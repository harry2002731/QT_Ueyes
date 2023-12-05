
/*******************************************************************************
** Qt Advanced Docking System
** Copyright (C) 2017 Uwe Kindler
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


//============================================================================
/// \file   MainWindow.cpp
/// \author Uwe Kindler
/// \date   13.02.2018
/// \brief  Implementation of CMainWindow demo class
//============================================================================


//============================================================================
//                                   INCLUDES
//============================================================================
#include <MainWindow.h>
#include "qstackedwidget.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QRegularExpression>
#include <iostream>

#include <QTime>
#include <QTimer>

#include <QLabel>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QFrame>
#include <QTreeView>
#include <QFileSystemModel>
#include <QBoxLayout>
#include <QSettings>
#include <QDockWidget>
#include <QDebug>
#include <QResizeEvent>
#include <QAction>
#include <QWidgetAction>
#include <QComboBox>
#include <QInputDialog>
#include <QRubberBand>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QScreen>
#include <QStyle>
#include <QMessageBox>
#include <QMenu>
#include <QToolButton>
#include <QToolBar>
#include <QPointer>
#include <QMap>
#include <QElapsedTimer>
#include <QQuickWidget>


#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
#include <QRandomGenerator>
#endif

#ifdef Q_OS_WIN
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <QAxWidget>
#endif
#endif

#include "DockManager.h"
#include "DockWidget.h"
#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"
#include "StatusDialog.h"
#include "ImageViewer.h"
#include "videopanel.h"
#include "SysInfoFetcher.h"

using namespace ads;

/**
 * Returns a random number from 0 to highest - 1
 */
int randomNumberBounded(int highest)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
	return QRandomGenerator::global()->bounded(highest);
#else
	qsrand(QTime::currentTime().msec());
	return qrand() % highest;
#endif
}

/**
 * Function returns a features string with closable (c), movable (m) and floatable (f)
 * features. i.e. The following string is for a not closable but movable and floatable
 * widget: c- m+ f+
 */
static QString featuresString(ads::CDockWidget* DockWidget)
{
	auto f = DockWidget->features();
	return QString("c%1 m%2 f%3")
		.arg(f.testFlag(ads::CDockWidget::DockWidgetClosable) ? "+" : "-")
		.arg(f.testFlag(ads::CDockWidget::DockWidgetMovable) ? "+" : "-")
		.arg(f.testFlag(ads::CDockWidget::DockWidgetFloatable) ? "+" : "-");
}


/**
 * Appends the string returned by featuresString() to the window title of
 * the given DockWidget
 */
static void appendFeaturStringToWindowTitle(ads::CDockWidget* DockWidget)
{
    DockWidget->setWindowTitle(DockWidget->windowTitle()
        +  QString(" (%1)").arg(featuresString(DockWidget)));
}

/**
 * Helper function to create an SVG icon
 */
static QIcon svgIcon(const QString& File)
{
	// This is a workaround, because in item views SVG icons are not
	// properly scaled and look blurry or pixelate
	QIcon SvgIcon(File);
	SvgIcon.addPixmap(SvgIcon.pixmap(92));
	return SvgIcon;
}


//============================================================================
class CCustomComponentsFactory : public ads::CDockComponentsFactory
{
public:
	using Super = ads::CDockComponentsFactory;
	ads::CDockAreaTitleBar* createDockAreaTitleBar(ads::CDockAreaWidget* DockArea) const override
	{
		auto TitleBar = new ads::CDockAreaTitleBar(DockArea);
		auto CustomButton = new QToolButton(DockArea);
		CustomButton->setToolTip(QObject::tr("Help"));
		CustomButton->setIcon(svgIcon(":/adsdemo/images/help_outline.svg"));
		CustomButton->setAutoRaise(true);
		int Index = TitleBar->indexOf(TitleBar->button(ads::TitleBarButtonTabsMenu));
		TitleBar->insertWidget(Index + 1, CustomButton);
		return TitleBar;
	}
};



//===========================================================================
/**
 * Custom QTableWidget with a minimum size hint to test CDockWidget
 * setMinimumSizeHintMode() function of CDockWidget
 */
class CMinSizeTableWidget : public QTableWidget
{
public:
	using QTableWidget::QTableWidget;
	virtual QSize minimumSizeHint() const override
	{
		return QSize(300, 100);
	}
};



//============================================================================
/**
 * Private data class pimpl
 */
struct MainWindowPrivate
{
	CMainWindow* _this;
	Ui::MainWindow ui;
    QAction* Welcome = nullptr;
    QAction* Designer = nullptr;
    QAction* Debugger = nullptr;
    QWidget* spacer = nullptr;
    QAction* Run = nullptr;
    QAction* RunOption = nullptr;
    QAction* ContinueRun = nullptr;

	QWidgetAction* PerspectiveListAction = nullptr;
	QComboBox* PerspectiveComboBox = nullptr;
	ads::CDockManager* DockManager = nullptr;
	ads::CDockWidget* WindowTitleTestDockWidget = nullptr;
	QPointer<ads::CDockWidget> LastDockedEditor;
	QPointer<ads::CDockWidget> LastCreatedFloatingEditor;
    QLabel *timeLabel;
    QLabel *memoryLabel;
	MainWindowPrivate(CMainWindow* _public) : _this(_public) {}

	 //初始化侧边栏所有action
    void createActions();

	//初始化侧边栏
    void createLeftToolBar();

	//初始化底部状态栏
    void createStatusBarActions();

    //添加窗体在内部
	void createContent();

	/**
	 * Saves the dock manager state and the main window geometry
	 */
    void saveState();

	/**
	 * Save the list of perspectives
	 */
	void savePerspectives();

	/**
	 * Restores the dock manager state
	 */
	void restoreState();

	/**
	 * Restore the perspective listo of the dock manager
	 */
	void restorePerspectives();

	/**
	 * Creates a dock widget with a file system tree view
	 */
	ads::CDockWidget* createFileSystemTreeDockWidget()
	{
		static int FileSystemCount = 0;
		QTreeView* w = new QTreeView();
		w->setFrameShape(QFrame::NoFrame);
		QFileSystemModel* m = new QFileSystemModel(w);
		m->setRootPath(QDir::currentPath());
		w->setModel(m);
		w->setRootIndex(m->index(QDir::currentPath()));
		ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Filesystem %1")
			.arg(FileSystemCount++));
		DockWidget->setWidget(w);
		DockWidget->setIcon(svgIcon(":/adsdemo/images/folder_open.svg"));
		ui.menuView->addAction(DockWidget->toggleViewAction());
		// We disable focus to test focus highlighting if the dock widget content
		// does not support focus
		w->setFocusPolicy(Qt::NoFocus);
		auto ToolBar = DockWidget->createDefaultToolBar();
		ToolBar->addAction(ui.actionSaveState);
		ToolBar->addAction(ui.actionRestoreState);
		return DockWidget;
	}

	/**
	 * Create a dock widget with a QCalendarWidget
	 */
	ads::CDockWidget* createCalendarDockWidget()
	{
		static int CalendarCount = 0;
		QCalendarWidget* w = new QCalendarWidget();
		ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Calendar %1").arg(CalendarCount++));
		// The following lines are for testing the setWidget() and takeWidget()
		// functionality
		DockWidget->setWidget(w);
		DockWidget->setWidget(w); // what happens if we set a widget if a widget is already set
		DockWidget->takeWidget(); // we remove the widget
		DockWidget->setWidget(w); // and set the widget again - there should be no error
        DockWidget->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);

		DockWidget->setIcon(svgIcon(":/adsdemo/images/date_range.svg"));
		ui.menuView->addAction(DockWidget->toggleViewAction());
        // 在窗体上方加入按键操作栏
        auto ToolBar = DockWidget->createDefaultToolBar();
        ToolBar->addAction(ui.actionSaveState);
        ToolBar->addAction(ui.actionRestoreState);
		return DockWidget;
	}

    /**
     * Create a dock widget with a QCalendarWidget
     */
    ads::CDockWidget* createStackedDockWidget()
    {
        static int CalendarCount = 0;
        QStackedWidget* w = new QStackedWidget();
        ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Calendar %1").arg(CalendarCount++));
        // The following lines are for testing the setWidget() and takeWidget()
        // functionality
        DockWidget->setWidget(w);
//        DockWidget->setWidget(w); // what happens if we set a widget if a widget is already set
//        DockWidget->takeWidget(); // we remove the widget
//        DockWidget->setWidget(w); // and set the widget again - there should be no error
        DockWidget->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
        DockWidget->setIcon(svgIcon(":/adsdemo/images/date_range.svg"));
        ui.menuView->addAction(DockWidget->toggleViewAction());
        // 在窗体上方加入按键操作栏
        auto ToolBar = DockWidget->createDefaultToolBar();
        ToolBar->addAction(ui.actionSaveState);
        ToolBar->addAction(ui.actionRestoreState);
        return DockWidget;
    }


	/**
	 * Create dock widget with a text label
	 */
	ads::CDockWidget* createLongTextLabelDockWidget()
	{
		static int LabelCount = 0;
		QLabel* l = new QLabel();
		l->setWordWrap(true);
		l->setAlignment(Qt::AlignTop | Qt::AlignLeft);

//		l->setText(QString("Label %1 %2 - Lorem ipsum dolor sit amet, consectetuer adipiscing elit. "
//			"Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque "
//			"penatibus et magnis dis parturient montes, nascetur ridiculus mus. "
//			"Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. "
//			"Nulla consequat massa quis enim. Donec pede justo, fringilla vel, "
//			"aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, "
//			"imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede "
//			"mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum "
//			"semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, "
//			"porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, "
//			"dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla "
//			"ut metus varius laoreet.")
//			.arg(LabelCount)
//			.arg(QTime::currentTime().toString("hh:mm:ss:zzz")));

		ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Label %1").arg(LabelCount++));
		DockWidget->setWidget(l);
		DockWidget->setIcon(svgIcon(":/adsdemo/images/font_download.svg"));
		ui.menuView->addAction(DockWidget->toggleViewAction());
		return DockWidget;
	}


	/**
	 * Creates as imple editor widget
	 */
	ads::CDockWidget* createEditorWidget()
	{
		static int EditorCount = 0;
		QPlainTextEdit* w = new QPlainTextEdit();
		w->setPlaceholderText("This is an editor. If you close the editor, it will be "
			"deleted. Enter your text here.");
		w->setStyleSheet("border: none");
		ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Editor %1").arg(EditorCount++));
		DockWidget->setWidget(w);
		DockWidget->setIcon(svgIcon(":/adsdemo/images/edit.svg"));
		DockWidget->setFeature(ads::CDockWidget::CustomCloseHandling, true);
		ui.menuView->addAction(DockWidget->toggleViewAction());

		QMenu* OptionsMenu = new QMenu(DockWidget);
		OptionsMenu->setTitle(QObject::tr("Options"));
		OptionsMenu->setToolTip(OptionsMenu->title());
		OptionsMenu->setIcon(svgIcon(":/adsdemo/images/custom-menu-button.svg"));
		auto MenuAction = OptionsMenu->menuAction();
		// The object name of the action will be set for the QToolButton that
		// is created in the dock area title bar. You can use this name for CSS
		// styling
		MenuAction->setObjectName("optionsMenu");
		DockWidget->setTitleBarActions({OptionsMenu->menuAction()});
		auto a = OptionsMenu->addAction(QObject::tr("Clear Editor"));
		w->connect(a, SIGNAL(triggered()), SLOT(clear()));

		return DockWidget;
	}

    //创建图片可视化窗口
    ads::CDockWidget* createImageViewerWidget()
	{
		static int ImageViewerCount = 0;
		auto w = new CImageViewer();
		auto ImageIndex = randomNumberBounded(4);
		auto FileName = ":adsdemo/images/ads_logo.svg";

		// Pick a random image from a number of images
		switch (ImageIndex)
		{
		case 0: FileName = ":adsdemo/images/ads_tile_blue.svg"; break;
		case 1: FileName = ":adsdemo/images/ads_tile_blue_light.svg"; break;
		case 2: FileName = ":adsdemo/images/ads_tile_green.svg"; break;
		case 3: FileName = ":adsdemo/images/ads_tile_orange.svg"; break;
		}

		auto Result = w->loadFile(FileName);
		qDebug() << "loadFile result: " << Result;
		ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Image Viewer %1").arg(ImageViewerCount++));
		DockWidget->setIcon(svgIcon(":/adsdemo/images/photo.svg"));
		DockWidget->setWidget(w,ads:: CDockWidget::ForceNoScrollArea);
		auto ToolBar = DockWidget->createDefaultToolBar();
        ToolBar->addActions(w->actions());
		return DockWidget;
	}

    //创建视频监视窗口
    ads::CDockWidget* createCameraViewerWidget()
    {
        static int CameraViewerCount = 0;
        auto w = new VideoPanel();
        ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(CameraViewerCount++));
        DockWidget->setWidget(w);
        return DockWidget;
    }

	/**
	 * Create a table widget
	 */
	ads::CDockWidget* createTableWidget()
	{
		static int TableCount = 0;
		auto w = new CMinSizeTableWidget();
		ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(TableCount++));
		static int colCount = 5;
		static int rowCount = 30;
		w->setColumnCount(colCount);
		w->setRowCount(rowCount);
		for (int col = 0; col < colCount; ++col)
		{
		  w->setHorizontalHeaderItem(col, new QTableWidgetItem(QString("Col %1").arg(col+1)));
		  for (int row = 0; row < rowCount; ++row)
		  {
			 w->setItem(row, col, new QTableWidgetItem(QString("T %1-%2").arg(row + 1).arg(col+1)));
		  }
		}
		DockWidget->setWidget(w);
		DockWidget->setIcon(svgIcon(":/adsdemo/images/grid_on.svg"));
		DockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromContent);
		auto ToolBar = DockWidget->createDefaultToolBar();
		auto Action = ToolBar->addAction(svgIcon(":/adsdemo/images/fullscreen.svg"), "Toggle Fullscreen");
		QObject::connect(Action, &QAction::triggered, [=]()
			{
				if (DockWidget->isFullScreen())
				{
					DockWidget->showNormal();
				}
				else
				{
					DockWidget->showFullScreen();
				}
			});
		ui.menuView->addAction(DockWidget->toggleViewAction());
		return DockWidget;
	}

	/**
	 * Create QQuickWidget for test for OpenGL and QQuick
	 */
	ads::CDockWidget *createQQuickWidget()
	{
		QQuickWidget *widget = new QQuickWidget();
		ads::CDockWidget *dockWidget = new ads::CDockWidget("Quick");
		dockWidget->setWidget(widget);
		return dockWidget;
	}


#ifdef Q_OS_WIN
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	/**
	 * Creates an ActiveX widget on windows
	 */
	ads::CDockWidget* createActiveXWidget(QWidget* parent = nullptr)
	{
	   static int ActiveXCount = 0;
	   QAxWidget* w = new QAxWidget("{6bf52a52-394a-11d3-b153-00c04f79faa6}", parent);
	   ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Active X %1").arg(ActiveXCount++));
	   DockWidget->setWidget(w);
	   ui.menuView->addAction(DockWidget->toggleViewAction());
	   return DockWidget;
	}
#endif
#endif
};

//============================================================================
void MainWindowPrivate::createContent()
{

    auto CameraViewer = createCameraViewerWidget();
    DockManager->addDockWidget(ads::LeftDockWidgetArea, CameraViewer);

    auto DockWidget = createLongTextLabelDockWidget();
    DockWidget->setFeature(ads::CDockWidget::DockWidgetFocusable, false);
    DockManager->addDockWidget(ads::BottomDockWidgetArea, DockWidget);

    DockWidget = createImageViewerWidget();
    DockManager->addDockWidget(ads::RightDockWidgetArea, DockWidget);

#ifdef Q_OS_WIN
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    DockManager->addDockWidget(ads::CenterDockWidgetArea, createActiveXWidget(), RighDockArea);
#endif
#endif

//	for (auto DockWidget : DockManager->dockWidgetsMap())
//	{
//		_this->connect(DockWidget, SIGNAL(viewToggled(bool)), SLOT(onViewToggled(bool)));
//		_this->connect(DockWidget, SIGNAL(visibilityChanged(bool)), SLOT(onViewVisibilityChanged(bool)));
//	}



//    // Create quick widget
//	DockWidget = createQQuickWidget();
//	DockWidget->setFeature(ads::CDockWidget::DockWidgetClosable, true);
//	DockManager->addDockWidget(ads::LeftDockWidgetArea, DockWidget);
}


//
void MainWindowPrivate::createLeftToolBar()
{
    ui.toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); //设置文字位置
    ui.toolBar->addAction(Welcome);
    ui.toolBar->addAction(Designer);
    ui.toolBar->addAction(Debugger);
    ui.toolBar->addWidget(spacer);
    ui.toolBar->addAction(RunOption);
    ui.toolBar->addSeparator(); //添加分割线
    ui.toolBar->addAction(Run);
    ui.toolBar->addAction(ContinueRun);

    PerspectiveListAction = new QWidgetAction(_this);
    PerspectiveComboBox = new QComboBox(_this);
    PerspectiveComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    PerspectiveComboBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    PerspectiveListAction->setDefaultWidget(PerspectiveComboBox);
}
//底部状态栏
void MainWindowPrivate::createStatusBarActions()
{
    QString imageName = "AdvancedDockingSystemDemo.exe";
    QLabel *loginLabel = new QLabel("登录：未登录");
    ui.statusBar->addWidget(loginLabel);

    // 右侧部分：版本号、时间和内存信息
    QLabel *versionLabel = new QLabel("版本号：1.0");
    timeLabel = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    auto sysinfo = new SysInfoFetcher();
    memoryLabel = new QLabel(sysinfo->MemFetcher(imageName));

    ui.statusBar->addPermanentWidget(versionLabel);
    ui.statusBar->addPermanentWidget(timeLabel);
    ui.statusBar->addPermanentWidget(memoryLabel);


}

void MainWindowPrivate::createActions()
{
    //欢迎按键设置
    Welcome = new QAction("欢迎", _this);
    Welcome->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
    _this->connect(Welcome, SIGNAL(triggered()), SLOT(changeState_triggered()));
    //Welcome->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");//提示内容

    //设计按键设置
    Designer = new QAction("设计", _this);
    Designer->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
    _this->connect(Designer, SIGNAL(triggered()), SLOT(changeState_triggered()));
    //Designer->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");

    //调试按键设置
    Debugger = new QAction("调试", _this);
    Debugger->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
    _this->connect(Debugger, SIGNAL(triggered()), SLOT(changeState_triggered()));
    //Debugger->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");

    //间隔设置
    spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //运行配置设置
    RunOption = new QAction("运行配置", _this);
    RunOption->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
    _this->connect(RunOption, SIGNAL(triggered()), SLOT(savePerspective()));
    //Debugger->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");

    //运行配置设置
    Run = new QAction("运行", _this);
    Run->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
    _this->connect(Run, SIGNAL(triggered()), SLOT(savePerspective()));
    //Debugger->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");

    //连续运行
    ContinueRun = new QAction("连续运行", _this);
    ContinueRun->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
    _this->connect(ContinueRun, SIGNAL(triggered()), SLOT(savePerspective()));
    //Debugger->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");
}

////保存窗体状态
//void MainWindowPrivate::saveState(QString page_name)
//{
//	QSettings Settings("Settings.ini", QSettings::IniFormat);
////	Settings.setValue("mainWindow/Geometry", _this->saveGeometry()); //用于复原窗体原先的位置
//	Settings.setValue("mainWindow/State", _this->saveState());
//    Settings.setValue(QString("mainWindow/%1").arg(page_name), DockManager->saveState());
//}

//保存窗体状态
void MainWindowPrivate::saveState()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    //	Settings.setValue("mainWindow/Geometry", _this->saveGeometry()); //用于复原窗体原先的位置
    Settings.setValue("mainWindow/State", _this->saveState());
    Settings.setValue(QString("mainWindow/DockingState"), DockManager->saveState());
}

void MainWindowPrivate::restoreState()
{
	QSettings Settings("Settings.ini", QSettings::IniFormat);
    _this->restoreGeometry(Settings.value("mainWindow/Geometry").toByteArray());
	_this->restoreState(Settings.value("mainWindow/State").toByteArray());
	DockManager->restoreState(Settings.value("mainWindow/DockingState").toByteArray());
}

//============================================================================


void MainWindowPrivate::savePerspectives()
{
	QSettings Settings("Settings.ini", QSettings::IniFormat);
	DockManager->savePerspectives(Settings);
}

//============================================================================
void MainWindowPrivate::restorePerspectives()
{
	QSettings Settings("Settings.ini", QSettings::IniFormat);
	DockManager->loadPerspectives(Settings);
	PerspectiveComboBox->clear();
	PerspectiveComboBox->addItems(DockManager->perspectiveNames());
}


//============================================================================
CMainWindow::CMainWindow(QWidget *parent) :
	QMainWindow(parent),
    d(new MainWindowPrivate(this))
{
    d->ui.setupUi(this);
    setWindowTitle(QApplication::instance()->applicationName());

    d->createActions(); //初始化所有action

    d->createStatusBarActions(); //初始化底部状态栏
    d->createLeftToolBar(); //初始化侧边栏

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMem()));
    timer->start(1000); // 每隔1秒触发一次 timeout 信号

    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);

    // uncomment if you would like to enable dock widget auto hiding
    CDockManager::setAutoHideConfigFlags({CDockManager::DefaultAutoHideConfig});

    d->DockManager = new CDockManager(this);
	#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
		connect(d->PerspectiveComboBox, SIGNAL(activated(QString)),
			d->DockManager, SLOT(openPerspective(QString)));
	#else
		connect(d->PerspectiveComboBox, SIGNAL(textActivated(QString)),
			d->DockManager, SLOT(openPerspective(QString)));
	#endif

    // Default window geometry - center on screen
    resize(640, 480);
    setGeometry(QStyle::alignedRect(
        Qt::LeftToRight, Qt::AlignCenter, frameSize(),
        QGuiApplication::primaryScreen()->availableGeometry()
    ));
    d->createContent(); //初始化主窗体

//    d->restoreState(); // 恢复成配置时的窗体布局
    d->restorePerspectives();
}

//============================================================================
CMainWindow::~CMainWindow()
{
	delete d;
}

void CMainWindow::updateTime()
{
    d->timeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void CMainWindow::updateMem()
{
    auto sysinfo = new SysInfoFetcher();
    d->memoryLabel->setText(sysinfo->MemFetcher("AdvancedDockingSystemDemo.exe"));
}



void CMainWindow::changeState_triggered()
{
    QAction *b = (QAction *)sender();
    QString name = b->text();

    QList<QAction *> tbtns = d->ui.toolBar->findChildren<QAction *>();
    foreach (QAction *btn, tbtns) {
        btn->setChecked(btn == b);
    }
    if (name == "欢迎") {
        d->restoreState();
    }
    else if (name == "设计") {
        d->restoreState();
    }
    else if (name == "调试") {
        d->restoreState();
    }
}


//============================================================================
void CMainWindow::closeEvent(QCloseEvent* event)
{
	d->saveState();
    // Delete dock manager here to delete all floating widgets. This ensures
    // that all top level windows of the dock manager are properly closed
    d->DockManager->deleteLater();
	QMainWindow::closeEvent(event);
}


//============================================================================
void CMainWindow::on_actionSaveState_triggered(bool)
{
	qDebug() << "MainWindow::on_actionSaveState_triggered";
	d->saveState();
}


//============================================================================
void CMainWindow::on_actionRestoreState_triggered(bool)
{
	qDebug() << "MainWindow::on_actionRestoreState_triggered";
	d->restoreState();
}


//============================================================================
void CMainWindow::savePerspective()
{
	QString PerspectiveName = QInputDialog::getText(this, "Save Perspective", "Enter unique name:");
	if (PerspectiveName.isEmpty())
	{
		return;
	}
	d->DockManager->addPerspective(PerspectiveName);
	QSignalBlocker Blocker(d->PerspectiveComboBox);
	d->PerspectiveComboBox->clear();
	d->PerspectiveComboBox->addItems(d->DockManager->perspectiveNames());
	d->PerspectiveComboBox->setCurrentText(PerspectiveName);

	d->savePerspectives();
}


//============================================================================
void CMainWindow::onViewToggled(bool Open)
{
	Q_UNUSED(Open);
	auto DockWidget = qobject_cast<ads::CDockWidget*>(sender());
	if (!DockWidget)
	{
		return;
	}

	//qDebug() << DockWidget->objectName() << " viewToggled(" << Open << ")";
}


//============================================================================
void CMainWindow::onViewVisibilityChanged(bool Visible)
{
	Q_UNUSED(Visible);
	auto DockWidget = qobject_cast<ads::CDockWidget*>(sender());
    if (!DockWidget)
    {
        return;
    }

    //qDebug() << DockWidget->objectName() << " visibilityChanged(" << Visible << ")";
}


//============================================================================
void CMainWindow::createEditor()
{
	QObject* Sender = sender();
	QVariant vFloating = Sender->property("Floating");
	bool Floating = vFloating.isValid() ? vFloating.toBool() : true;
	QVariant vTabbed = Sender->property("Tabbed");
	bool Tabbed = vTabbed.isValid() ? vTabbed.toBool() : true;
	auto DockWidget = d->createEditorWidget();
	DockWidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
	DockWidget->setFeature(ads::CDockWidget::DockWidgetForceCloseWithArea, true);
    connect(DockWidget, SIGNAL(closeRequested()), SLOT(onEditorCloseRequested()));

    if (Floating)
    {
		auto FloatingWidget = d->DockManager->addDockWidgetFloating(DockWidget);
		FloatingWidget->move(QPoint(20, 20));
		d->LastCreatedFloatingEditor = DockWidget;
		d->LastDockedEditor.clear();
		return;
    }


	ads::CDockAreaWidget* EditorArea = d->LastDockedEditor ? d->LastDockedEditor->dockAreaWidget() : nullptr;
	if (EditorArea)
	{
		if (Tabbed)
		{
			// Test inserting the dock widget tab at a given position instead
			// of appending it. This function inserts the new dock widget as
			// first tab
			d->DockManager->addDockWidgetTabToArea(DockWidget, EditorArea, 0);
		}
		else
		{
			d->DockManager->setConfigFlag(ads::CDockManager::EqualSplitOnInsertion, true);
			d->DockManager->addDockWidget(ads::RightDockWidgetArea, DockWidget, EditorArea);
		}
	}
	else
	{
		if (d->LastCreatedFloatingEditor)
		{
			d->DockManager->addDockWidget(ads::RightDockWidgetArea, DockWidget, d->LastCreatedFloatingEditor->dockAreaWidget());
		}
		else
		{
			d->DockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);
		}
	}
	d->LastDockedEditor = DockWidget;
}


//============================================================================
void CMainWindow::onEditorCloseRequested()
{
	auto DockWidget = qobject_cast<ads::CDockWidget*>(sender());
	int Result = QMessageBox::question(this, "Close Editor", QString("Editor %1 "
		"contains unsaved changes? Would you like to close it?")
		.arg(DockWidget->windowTitle()));
	if (QMessageBox::Yes == Result)
	{
		DockWidget->closeDockWidget();
	}
}


//============================================================================
void CMainWindow::onImageViewerCloseRequested()
{
	auto DockWidget = qobject_cast<ads::CDockWidget*>(sender());
	int Result = QMessageBox::question(this, "Close Image Viewer", QString("%1 "
		"contains unsaved changes? Would you like to close it?")
		.arg(DockWidget->windowTitle()));
	if (QMessageBox::Yes == Result)
	{
		DockWidget->closeDockWidget();
	}
}


//============================================================================
void CMainWindow::createTable()
{
	auto DockWidget = d->createTableWidget();
	DockWidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
	auto FloatingWidget = d->DockManager->addDockWidgetFloating(DockWidget);
    FloatingWidget->move(QPoint(40, 40));
}


//============================================================================
void CMainWindow::showStatusDialog()
{
	CStatusDialog Dialog(d->DockManager);
	Dialog.exec();
}


//============================================================================
void CMainWindow::toggleDockWidgetWindowTitle()
{
	QString Title = d->WindowTitleTestDockWidget->windowTitle();
	int i = Title.indexOf(" (Test)");
	if (-1 == i)
	{
		Title += " (Test)";
	}
	else
	{
		Title = Title.left(i);
	}
	d->WindowTitleTestDockWidget->setWindowTitle(Title);
}


//============================================================================
void CMainWindow::applyVsStyle()
{
	QFile StyleSheetFile(":adsdemo/res/visual_studio_light.css");
	StyleSheetFile.open(QIODevice::ReadOnly);
	QTextStream StyleSheetStream(&StyleSheetFile);
	auto Stylesheet = StyleSheetStream.readAll();
	StyleSheetFile.close();
	d->DockManager->setStyleSheet(Stylesheet);
}


//============================================================================
void CMainWindow::createImageViewerWidget()
{
	QAction* a = qobject_cast<QAction*>(sender());
    qDebug() << "createImageViewerWidget " << a->text();

    auto DockWidget = d->createImageViewerWidget();
	DockWidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
	DockWidget->setFeature(ads::CDockWidget::DockWidgetForceCloseWithArea, true);
	DockWidget->setFeature(ads::CDockWidget::CustomCloseHandling, true);
	DockWidget->resize(QSize(640, 480));
	connect(DockWidget, &ads::CDockWidget::closeRequested, this,
		&CMainWindow::onImageViewerCloseRequested);

	if (a->text().startsWith("Floating"))
	{
		auto FloatingWidget = d->DockManager->addDockWidgetFloating(DockWidget);
		FloatingWidget->move(QPoint(20, 20));
	}
	else if (a->text().startsWith("Docked"))
	{
		d->DockManager->addDockWidget(ads::RightDockWidgetArea, DockWidget);
	}
	else if (a->text().startsWith("Pinned"))
	{
		d->DockManager->addAutoHideDockWidget(ads::SideBarLeft, DockWidget);
	}
}

