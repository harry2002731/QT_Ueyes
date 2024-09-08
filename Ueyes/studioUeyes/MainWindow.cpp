
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
#include "qpainter.h"
#include "ui_mainwindow.h"
#include <QtConcurrent/QtConcurrent>
using namespace QtConcurrent;

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


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
#include <QRadioButton>

#include <QSqlDatabase>

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
#include "DockComponentsFactory.h"
#include "SysInfoFetcher.h"
#include <QStackedLayout>
#include "BasicWindow.h"
#include "WelcomeWindow.h"
#include "DesignWindow.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Widget_Lib/LoginViewer/LoginView/src/lvmainmodel.h"
#include <QQuickStyle>
#include <QQuickView>
#include <QPainterPath>
#include <QWKWidgets/widgetwindowagent.h>
#include "shared/widgetframe/windowbar.h"
#include "shared/widgetframe/windowbutton.h"

//QStackedLayout* m_layout;
using namespace ads;
using namespace cv;

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
 * 通过设定固定大小，保证icon显示正常
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
    QMap<QString,QPointer<BasicWindow>> win_map;

//    ads::CDockManager* DockManager = nullptr;
    QWidget m_welcomeWidget;
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

    void deleteLater();


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


//
void MainWindowPrivate::createLeftToolBar()
{

//    ui.actionSaveState->setIcon(svgIcon(":/adsdemo/images/save.svg"));
//    ui.toolBar_->addAction(ui.actionSaveState);
//    ui.actionRestoreState->setIcon(svgIcon(":/adsdemo/images/restore.svg"));
//    ui.toolBar_->addAction(ui.actionRestoreState);
//    ui.toolBar_2->addAction(Debugger);


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
    // memoryLabel = new QLabel(sysinfo->MemFetcher(imageName));

    ui.statusBar->addPermanentWidget(versionLabel);
    ui.statusBar->addPermanentWidget(timeLabel);
    // ui.statusBar->addPermanentWidget(memoryLabel);
}


void MainWindowPrivate::createActions()
{
    //欢迎按键设置
    Welcome = new QAction("欢迎", _this);
    Welcome->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
//    Welcome->setCheckable(true);
    _this->connect(Welcome, SIGNAL(triggered()), SLOT(changeState_triggered()));
    //Welcome->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");//提示内容

//    //设计按键设置
    Designer = new QAction("设计", _this);
    Designer->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
    _this->connect(Designer, SIGNAL(triggered()), SLOT(changeState_triggered()));
//    //Designer->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");

//    //调试按键设置
//    Debugger = new QAction("调试", _this);
//    Debugger->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
//    _this->connect(Debugger, SIGNAL(triggered()), SLOT(changeState_triggered()));
    //Debugger->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");

//    Debugger = new QAction("登录", _this);
//    Debugger->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
//    _this->connect(Debugger, SIGNAL(triggered()), SLOT(changeState_triggered()));
//    Debugger->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");
    //间隔设置
//    spacer = new QWidget();
//    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    //运行配置设置
//    RunOption = new QAction("运行配置", _this);
//    RunOption->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
//    _this->connect(RunOption, SIGNAL(triggered()), SLOT(savePerspective()));
//    //Debugger->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");

//    //运行配置设置
//    Run = new QAction("运行", _this);
//    Run->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
//    _this->connect(Run, SIGNAL(triggered()), SLOT(savePerspective()));
//    //Debugger->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");

//    //连续运行
//    ContinueRun = new QAction("连续运行", _this);
//    ContinueRun->setIcon(svgIcon(":/adsdemo/images/picture_in_picture.svg"));
//    _this->connect(ContinueRun, SIGNAL(triggered()), SLOT(savePerspective()));
    //Debugger->setToolTip("Creates floating dynamic dockable editor windows that are deleted on close");
}


//保存窗体状态
void MainWindowPrivate::saveState()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    //	Settings.setValue("mainWindow/Geometry", _this->saveGeometry()); //用于复原窗体原先的位置
    Settings.setValue("mainWindow/State", _this->saveState());

    //对每个窗体进行dock状态的保存
    QMap<QString,QPointer<BasicWindow>>::Iterator it=win_map.begin();
    while(it!=win_map.end())
    {
       it.value()->saveDockState();
       it++;
    }
}

void MainWindowPrivate::deleteLater()
{
    //对每个窗体进行dock状态的保存
    QMap<QString,QPointer<BasicWindow>>::Iterator it=win_map.begin();
    while(it!=win_map.end())
    {
       it.value()->deleteLater();
       it++;
    }
}

void MainWindowPrivate::restoreState()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    _this->restoreGeometry(Settings.value("mainWindow/Geometry").toByteArray());
    _this->restoreState(Settings.value("mainWindow/State").toByteArray());


    //复原之前的dock状态
    QMap<QString,QPointer<BasicWindow>>::Iterator it=win_map.begin();
    while(it!=win_map.end())
    {
       it.value()->restoreDockState();
       it++;
    }
}

//保存所有窗体的状态==============================================================
void MainWindowPrivate::savePerspectives()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    QMap<QString,QPointer<BasicWindow>>::Iterator it=win_map.begin();
    while(it!=win_map.end())
    {
       it.value()->saveDockPerspectives();
       it++;
    }
}

//复原所有窗体的状态===============================================================
void MainWindowPrivate::restorePerspectives()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    QMap<QString,QPointer<BasicWindow>>::Iterator it=win_map.begin();
    PerspectiveComboBox->clear();

    while(it!=win_map.end())
    {
       it.value()->restoreDockPerspectives();
       PerspectiveComboBox->addItems(it.value()->perspectiveNames());
       it++;
    }
}

class Worker : public QObject
{
    Q_OBJECT

public:
    QLabel *time_Label,*memory_label;
    Worker(QLabel *timeLabel,QLabel *memoryLabel) {
       time_Label = timeLabel;
       memory_label = memoryLabel;
    }

public slots:
    void doWork() {
       QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
       connect(timer, SIGNAL(timeout()), this, SLOT(updateMem()));
       timer->start(1000); // 每隔1秒触发一次 timeout 信号

    }
    void updateTime()
    {
       time_Label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    }
    void updateMem()
    {
       // auto sysinfo = new SysInfoFetcher();
       // memory_label->setText(sysinfo->MemFetcher("AdvancedDockingSystemDemo.exe"));
    }

};

void CMainWindow::installWindowAgent() {
//     // 1. Setup window agent
    windowAgent = new QWK::WidgetWindowAgent(this);
    windowAgent->setup(this);
    loadStyleSheet(Dark);

    // 2. Construct your title bar
    auto menuBar = [this]() {
        auto menuBar = new QMenuBar();

        // Virtual menu
        auto file = new QMenu(tr("文件(&F)"), menuBar);
        auto system = new QMenu(tr("系统(&N)"), menuBar);
        auto tool = new QMenu(tr("工具(&T)"), menuBar);
        auto setting = new QMenu(tr("设置(&S)"), menuBar);
        QAction* save = new QAction(tr("保存窗体"),menuBar);
        QAction* restore = new QAction(tr("恢复窗体"),menuBar);

        setting->addAction(save);
        setting->addAction(restore);

        auto help = new QMenu(tr("帮助(&H)"), menuBar);

        connect(save, &QAction::triggered, this, &CMainWindow::on_actionSaveState_triggered);
        connect(restore, &QAction::triggered, this, &CMainWindow::on_actionRestoreState_triggered);

//        this->connect(save, SIGNAL(triggered()), SLOT(on_actionSaveState_triggered()));
//        this->connect(restore, SIGNAL(triggered()), SLOT(on_actionRestoreState_triggered()));

//        file->addSeparator();

//        auto edit = new QMenu(tr("Edit(&E)"), menuBar);
//        edit->addAction(new QAction(tr("Undo(&U)"), menuBar));
//        edit->addAction(new QAction(tr("Redo(&R)"), menuBar));

        // Theme action
        auto darkAction = new QAction(tr("Enable dark theme"), menuBar);
        darkAction->setCheckable(true);
//        connect(darkAction, &QAction::triggered, this, [this](bool checked) {
//            loadStyleSheet(checked ? Dark : Light); //
//        });
        connect(this, &CMainWindow::themeChanged, darkAction, [this, darkAction]() {
            darkAction->setChecked(currentTheme == Dark); //
        });

#ifdef Q_OS_WIN
        auto dwmBlurAction = new QAction(tr("Enable DWM blur"), menuBar);
        dwmBlurAction->setCheckable(true);
        connect(dwmBlurAction, &QAction::toggled, this, [this](bool checked) {
            if (!windowAgent->setWindowAttribute(QStringLiteral("dwm-blur"), checked)) {
                return;
            }
            setProperty("custom-style", checked);
            style()->polish(this);
        });

        auto acrylicAction = new QAction(tr("Enable acrylic material"), menuBar);
        acrylicAction->setCheckable(true);
        connect(acrylicAction, &QAction::toggled, this, [this](bool checked) {
            if (!windowAgent->setWindowAttribute(QStringLiteral("acrylic-material"), true)) {
                return;
            }
            setProperty("custom-style", checked);
            style()->polish(this);
        });

        auto micaAction = new QAction(tr("Enable mica"), menuBar);
        micaAction->setCheckable(true);
        connect(micaAction, &QAction::toggled, this, [this](bool checked) {
            if (!windowAgent->setWindowAttribute(QStringLiteral("mica"), checked)) {
                return;
            }
            setProperty("custom-style", checked);
            style()->polish(this);
        });

        auto micaAltAction = new QAction(tr("Enable mica alt"), menuBar);
        micaAltAction->setCheckable(true);
        connect(micaAltAction, &QAction::toggled, this, [this](bool checked) {
            if (!windowAgent->setWindowAttribute(QStringLiteral("mica-alt"), checked)) {
                return;
            }
            setProperty("custom-style", checked);
            style()->polish(this);
        });
#elif defined(Q_OS_MAC)
        auto darkBlurAction = new QAction(tr("Dark blur"), menuBar);
        darkBlurAction->setCheckable(true);
        connect(darkBlurAction, &QAction::toggled, this, [this](bool checked) {
            if (!windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "dark")) {
                return;
            }
            if (checked) {
                setProperty("custom-style", true);
                style()->polish(this);
            }
        });

        auto lightBlurAction = new QAction(tr("Light blur"), menuBar);
        lightBlurAction->setCheckable(true);
        connect(lightBlurAction, &QAction::toggled, this, [this](bool checked) {
            if (!windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "light")) {
                return;
            }
            if (checked) {
                setProperty("custom-style", true);
                style()->polish(this);
            }
        });

        auto noBlurAction = new QAction(tr("No blur"), menuBar);
        noBlurAction->setCheckable(true);
        connect(noBlurAction, &QAction::toggled, this, [this](bool checked) {
            if (!windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "none")) {
                return;
            }
            if (checked) {
                setProperty("custom-style", false);
                style()->polish(this);
            }
        });

        auto macStyleGroup = new QActionGroup(menuBar);
        macStyleGroup->addAction(darkBlurAction);
        macStyleGroup->addAction(lightBlurAction);
        macStyleGroup->addAction(noBlurAction);
#endif

        // Real menu
//        auto settings = new QMenu(tr("Settings(&S)"), menuBar);
//        settings->addAction(darkAction);

#ifdef Q_OS_WIN
//        settings->addSeparator();
//        settings->addAction(dwmBlurAction);
//        settings->addAction(acrylicAction);
//        settings->addAction(micaAction);
//        settings->addAction(micaAltAction);
#elif defined(Q_OS_MAC)
        settings->addAction(darkBlurAction);
        settings->addAction(lightBlurAction);
        settings->addAction(noBlurAction);
#endif

        menuBar->addMenu(file);
        menuBar->addMenu(system);
        menuBar->addMenu(tool);
        menuBar->addMenu(setting);
        menuBar->addMenu(help);

        return menuBar;
    }();
    menuBar->setObjectName(QStringLiteral("win-menu-bar"));

    auto titleLabel = new QLabel();
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName(QStringLiteral("win-title-label"));

#ifndef Q_OS_MAC
    auto iconButton = new QWK::WindowButton();
    iconButton->setObjectName(QStringLiteral("icon-button"));
    iconButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto minButton = new QWK::WindowButton();
    minButton->setObjectName(QStringLiteral("min-button"));
    minButton->setProperty("system-button", true);
    minButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto maxButton = new QWK::WindowButton();
    maxButton->setCheckable(true);
    maxButton->setObjectName(QStringLiteral("max-button"));
    maxButton->setProperty("system-button", true);
    maxButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto closeButton = new QWK::WindowButton();
    closeButton->setObjectName(QStringLiteral("close-button"));
    closeButton->setProperty("system-button", true);
    closeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
#endif

    auto windowBar = new QWK::WindowBar();
#ifndef Q_OS_MAC
    windowBar->setIconButton(iconButton);
    windowBar->setMinButton(minButton);
    windowBar->setMaxButton(maxButton);
    windowBar->setCloseButton(closeButton);
#endif
    windowBar->setMenuBar(menuBar);
    windowBar->setTitleLabel(titleLabel);
    windowBar->setHostWidget(this);

    windowAgent->setTitleBar(windowBar);
#ifndef Q_OS_MAC
    windowAgent->setSystemButton(QWK::WindowAgentBase::WindowIcon, iconButton);
    windowAgent->setSystemButton(QWK::WindowAgentBase::Minimize, minButton);
    windowAgent->setSystemButton(QWK::WindowAgentBase::Maximize, maxButton);
    windowAgent->setSystemButton(QWK::WindowAgentBase::Close, closeButton);
#endif
    windowAgent->setHitTestVisible(menuBar, true);

#ifdef Q_OS_MAC
    windowAgent->setSystemButtonAreaCallback([](const QSize &size) {
        static constexpr const int width = 75;
        return QRect(QPoint(size.width() - width, 0), QSize(width, size.height())); //
    });
#endif

    setMenuWidget(windowBar);


#ifndef Q_OS_MAC
    connect(windowBar, &QWK::WindowBar::minimizeRequested, this, &QWidget::showMinimized);
    connect(windowBar, &QWK::WindowBar::maximizeRequested, this, [this, maxButton](bool max) {
        if (max) {
            showMaximized();
        } else {
            showNormal();
        }

        // It's a Qt issue that if a QAbstractButton::clicked triggers a window's maximization,
        // the button remains to be hovered until the mouse move. As a result, we need to
        // manually send leave events to the button.
//        emulateLeaveEvent(maxButton);
    });
    connect(windowBar, &QWK::WindowBar::closeRequested, this, &QWidget::close);
#endif
}

//============================================================================
CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    d(new MainWindowPrivate(this))
{
    setMouseTracking(true); // 启用鼠标跟踪
    d->ui.setupUi(this);
    installWindowAgent();

    setWindowTitle(QApplication::instance()->applicationName());

    d->createActions(); //初始化所有action
    d->createStatusBarActions(); //初始化底部状态栏
    d->createLeftToolBar(); //初始化侧边栏

    QTimer *timer = new QTimer(this);
    QThread* pthread = new QThread();
    Worker* worker = new Worker(d->timeLabel,d->memoryLabel); // 创建一个Worker对象
    worker->moveToThread(pthread); // 将Worker对象移动到新线程中
    QObject::connect(pthread, &QThread::started, worker, &Worker::doWork); // 连接信号和槽函数
    pthread->start();
    timer->start(1000); // 每隔1秒触发一次 timeout 信号



    CDockManager::setConfigFlag(CDockManager::FocusHighlighting, true);
    CDockManager::setAutoHideConfigFlags({CDockManager::DefaultAutoHideConfig});


    d->ui.widget->setLayout(m_layout = new QStackedLayout());
    auto basic_win = new BasicWindow(d->ui.widget,QString("basic"));
    auto welcome_win = new WelcomeWindow(d->ui.widget,QString("welcome"));
    auto design_win = new DesignWindow(d->ui.widget,QString("debug"));

    d->win_map.insert("basic",basic_win);
    d->win_map.insert("welcome",welcome_win);
    // d->win_map.insert("debug",design_win);


    d->ui.widget->layout()->addWidget(basic_win);//显示调用layout来进行布局
    d->ui.widget->layout()->addWidget(welcome_win);//显示调用layout来进行布局
    // d->ui.widget->layout()->addWidget(design_win);//显示调用layout来进行布局

    basic_win->createContent();
    welcome_win->createContent();
    // design_win->createContent();


   auto pWidget = new QWidget();
   pWidget->setGeometry(0,0,d->ui.widget->geometry().width(),d->ui.widget->geometry().height());
   pWidget->setStyleSheet("background-color: rgba(128, 128, 128, 127);"); // 设置半透明的灰色背景
   pWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


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

   d->restorePerspectives();
}

//void CMainWindow::mousePressEvent(QMouseEvent *event) {
//    if (!isLoggedIn && event->button() == Qt::LeftButton) {
//       // 如果用户未登录，点击窗体则弹出登录对话框
//       QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    }
//    QMainWindow::mousePressEvent(event);

//}

//============================================================================
CMainWindow::~CMainWindow()
{
    delete d;
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
        d->win_map["debug"]->hideManagerAndFloatingWidgets();
        m_layout->setCurrentWidget(d->win_map["welcome"]);
    }
    else if (name == "设计") {
        d->win_map["welcome"]->hideManagerAndFloatingWidgets();
        m_layout->setCurrentWidget(d->win_map["debug"]);
    }
//    else if (name == "调试") {
//        d->win_map["welcome"]->hideManagerAndFloatingWidgets();
//        m_layout->setCurrentWidget(d->win_map["debug"]);
//    }

    else if (name == "登录") {
//        QWidget * aaa = new QWidget();
//        int DataViewerCount = 0;
//        ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(DataViewerCount++));
//        DockWidget->setWidget(aaa);

//        auto FloatingWidget = d->DockManager->addDockWidgetFloating(DockWidget);
//        FloatingWidget->move(QPoint(20, 20));
    }
}


//============================================================================
void CMainWindow::closeEvent(QCloseEvent* event)
{
    d->saveState();
    //在Qt中，deleteLater() 是一个槽函数，用于安全地删除一个对象。
    //它在稍后的事件循环中异步删除对象，而不是立即删除，
    //以确保在对象被删除之前它的槽函数执行完成。
    d->deleteLater();
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
//    d->DockManager->addPerspective(PerspectiveName);
    QSignalBlocker Blocker(d->PerspectiveComboBox);
    d->PerspectiveComboBox->clear();
//    d->PerspectiveComboBox->addItems(d->DockManager->perspectiveNames());
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
void CMainWindow::showStatusDialog()
{
//    CStatusDialog Dialog(d->DockManager);
//    Dialog.exec();
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
    QFile StyleSheetFile(":adsdemo/visual_studio_light.css");
    StyleSheetFile.open(QIODevice::ReadOnly);
    QTextStream StyleSheetStream(&StyleSheetFile);
    auto Stylesheet = StyleSheetStream.readAll();
    StyleSheetFile.close();
//    d->DockManager->setStyleSheet(Stylesheet);
}
#include "MainWindow.moc"


void CMainWindow::loadStyleSheet(Theme theme) {
    if (!styleSheet().isEmpty() && theme == currentTheme)
        return;
    currentTheme = theme;

    if (QFile qss(theme == Dark ? QStringLiteral(":/dark-style.qss")
                                : QStringLiteral(":/light-style.qss"));
        qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(QString::fromUtf8(qss.readAll()));
        Q_EMIT themeChanged();
    }
}
bool CMainWindow::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::WindowActivate: {
        auto menu = menuWidget();
        if (menu) {
            menu->setProperty("bar-active", true);
            style()->polish(menu);
        }
        break;
    }

    case QEvent::WindowDeactivate: {
        auto menu = menuWidget();
        if (menu) {
            menu->setProperty("bar-active", false);
            style()->polish(menu);
        }
        break;
    }

    default:
        break;
    }
    return QMainWindow::event(event);
}

