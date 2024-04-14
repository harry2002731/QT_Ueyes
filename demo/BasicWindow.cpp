#include "BasicWindow.h"
#include "Widget_Lib/FuncViewer/FuncViewerWidget.h"
#include "BaseFunc_Lib/BaseFunc_Lib.h"
#include <QStandardItemModel>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Widget_Lib/LoginViewer/LoginView/src/lvmainmodel.h"
#include <QQuickStyle>
#include <QQuickView>

using namespace ads;


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
重写QTableWidget的最小窗体大小
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


//此处BasicWindow作为基类用来继承，继承出的类都会作为切换的页面。
//核心是将CDockManager作为页面管理器。
BasicWindow::BasicWindow(QWidget *parent,QString name):
    CDockManager(parent)
{
    win_name = name;
}

//添加窗体在内部
void BasicWindow::createContent()
{
    auto CameraViewer = createCameraViewerWidget();
    this->addDockWidget(ads::LeftDockWidgetArea, CameraViewer);
    auto FileSystemTreeViewer = createFileSystemTreeDockWidget();
    this->addDockWidget(ads::BottomDockWidgetArea, FileSystemTreeViewer );

    auto imageViewer = createImageViewerWidget();
    this->addDockWidget(ads::LeftDockWidgetArea, imageViewer );

    auto aaa = test();
    this->addDockWidget(ads::LeftDockWidgetArea, aaa );

    auto bbb = loginViewer();
    this->addDockWidget(ads::LeftDockWidgetArea, bbb );

//    SqlLite_Lib();
}

/**
 * Saves the dock manager state and the main window geometry
 */
void BasicWindow::saveDockState()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    Settings.setValue(QString("%1/DockingState").arg(win_name), this->saveState());
    //Settings.setValue("mainWindow/Geometry", _this->saveGeometry()); //用于复原窗体原先的位置
}
/**
 * Save the list of perspectives
 */
void BasicWindow::saveDockPerspectives()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    this->savePerspectives(Settings);
}
/**
 * Restores the dock manager state
 */
void BasicWindow::restoreDockState()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    this->restoreState(Settings.value(QString("%1/DockingState").arg(win_name)).toByteArray());
}
/**
 * Restore the perspective listo of the dock manager
 */
void BasicWindow::restoreDockPerspectives()
{
    QSettings Settings("Settings.ini", QSettings::IniFormat);
    this->loadPerspectives(Settings);
//    PerspectiveComboBox->clear();
//    PerspectiveComboBox->addItems(DockManager->perspectiveNames());
}

/**
 * Creates a dock widget with a file system tree view
 */
ads::CDockWidget* BasicWindow::createFileSystemTreeDockWidget()
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
    // We disable focus to test focus highlighting if the dock widget content
    // does not support focus
    w->setFocusPolicy(Qt::NoFocus);
    return DockWidget;
}


//创建不可修改的label文本窗体
ads::CDockWidget* BasicWindow::createLabelDockWidget()
{
    static int LabelCount = 0;
    QLabel* l = new QLabel();
    l->setWordWrap(true);
    l->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    l->setText(QString(""));
    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Label %1").arg(LabelCount++));
    DockWidget->setWidget(l);
    DockWidget->setIcon(svgIcon(":/adsdemo/images/font_download.svg"));
    return DockWidget;
}


//创建可修改的文本窗体
ads::CDockWidget* BasicWindow::createEditorWidget()
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

////创建图片可视化窗口
ads::CDockWidget* BasicWindow::createImageViewerWidget()
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
ads::CDockWidget* BasicWindow::createCameraViewerWidget()
{
    static int CameraViewerCount = 0;
    auto w = new VideoPanel();
    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(CameraViewerCount++));
    DockWidget->setWidget(w);
    DockWidget->setMinimumSize(100,100);

    DockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidgetMinimumSize);
    return DockWidget;
}


ads::CDockWidget* BasicWindow::createTest()
{
    static int CameraViewerCount = 0;
    auto w = new FuncViewerWidget();
    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(CameraViewerCount++));
    DockWidget->setWidget(w);
    return DockWidget;
}

//************显示调用动态库效果测试*****************
typedef FuncViewerWidget* (*CREATE_WIDGET) ();

//ads::CDockWidget* BasicWindow::test()
//{
//    static int widget = 0;
//    HINSTANCE hDLL = LoadLibrary(L"libWidgetLib.dll");
//    CREATE_WIDGET pEntryFunction = (CREATE_WIDGET)GetProcAddress(hDLL,"CreateWidget");

//    FuncViewerWidget* pMath = pEntryFunction();
//    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(widget++));

//    if (pMath) {
//        std::cout << "success" << std::endl;
//        pMath->addPageWidget("test_widget",new QWidget());
//        DockWidget->setWidget(pMath);

//    }
//    return DockWidget;
//}

//动态库调用
ads::CDockWidget* BasicWindow::test()
{
    static int widget = 0;
    auto aaa = BaseFunc_Lib();
    auto pMath = aaa.loadLibFunc<FuncViewerWidget*>(QString("libWidgetLib.dll"),"CreateWidget");
    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(widget++));

    if (pMath) {
        pMath->addPageWidget("test_widget",new QWidget());

        DockWidget->setWidget(pMath);

    }
    return DockWidget;
}
//********************************************

//**************插件测试***********************


ads::CDockWidget* BasicWindow::loadPlugin(){
    QPluginLoader pluginLoader("D:\\Projects\\QTProjects\\QT_Ueyes\\build-QT_Ueyes-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\modules\\SqlLite_Lib\\libSqlLite_Lib.dll");
    QObject *plugin = pluginLoader.instance();


    m_pInterface = qobject_cast<DeclareInterface *>(plugin);
    QString db_name  = "C:\\Users\\HarryWen\\Desktop\\test.db";
    QSqlDatabase db = m_pInterface->connectDB(db_name);
    m_pInterface->getTableInfo(db,"EC");
    QTableWidget* tableView = m_pInterface->createWidget();
    static int widget2 = 0;
    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table111 %1").arg(widget2++));
    DockWidget->setWidget(tableView);
    DockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidgetMinimumSize);
    return DockWidget;
}

//********************************************

ads::CDockWidget* BasicWindow::loginViewer()
{
    QQuickWidget* widget = new QQuickWidget();

//    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QQuickStyle::setStyle("Material");
    LoginView::LVMainModel loginModel("exampleLogin");
    if (!loginModel.init(widget)) {
        qDebug() << "1111";
    }

    QString pathXML = ":/example.xml";

    if (!loginModel.setCounrySource(pathXML)) {
        qDebug() << "2222 ";
    }

//    QObject::connect(&widget, &QQmlApplicationEngine::objectCreated,
//        &app, [url](QObject *obj, const QUrl &objUrl) {
//        }, Qt::QueuedConnection);

//    engine.load(url);
    widget -> setSource(url);
    static int CameraViewerCount = 0;
    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(CameraViewerCount++));
    DockWidget->setWidget(widget);
    return DockWidget;


}

//创建表格窗口
ads::CDockWidget* BasicWindow::createTableWidget()
{
    static int TableCount = 0;
    auto w = new CMinSizeTableWidget();
    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(TableCount++));
    static int colCount = 5;
    static int rowCount = 30;
    w->setColumnCount(colCount);
    w->setRowCount(rowCount);

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
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
    return DockWidget;
}

/**
     * Create QQuickWidget for test for OpenGL and QQuick
     */
ads::CDockWidget *BasicWindow::createQQuickWidget()
{
    QQuickWidget *widget = new QQuickWidget();
    ads::CDockWidget *dockWidget = new ads::CDockWidget("Quick");
    dockWidget->setWidget(widget);
    return dockWidget;
}


void BasicWindow::applyVsStyle()
{
    QFile StyleSheetFile(":adsdemo/res/visual_studio_light.css");
    StyleSheetFile.open(QIODevice::ReadOnly);
    QTextStream StyleSheetStream(&StyleSheetFile);
    auto Stylesheet = StyleSheetStream.readAll();
    StyleSheetFile.close();
    this->setStyleSheet(Stylesheet);
}


////============================================================================
//void CMainWindow::onEditorCloseRequested()
//{
//    auto DockWidget = qobject_cast<ads::CDockWidget*>(sender());
//    int Result = QMessageBox::question(this, "Close Editor", QString("Editor %1 "
//                                                                     "contains unsaved changes? Would you like to close it?")
//                                                                 .arg(DockWidget->windowTitle()));
//    if (QMessageBox::Yes == Result)
//    {
//        DockWidget->closeDockWidget();
//    }
//}


////============================================================================
//void CMainWindow::onImageViewerCloseRequested()
//{
//    auto DockWidget = qobject_cast<ads::CDockWidget*>(sender());
//    int Result = QMessageBox::question(this, "Close Image Viewer", QString("%1 "
//                                                                           "contains unsaved changes? Would you like to close it?")
//                                                                       .arg(DockWidget->windowTitle()));
//    if (QMessageBox::Yes == Result)
//    {
//        DockWidget->closeDockWidget();
//    }
//}
