#include "WelcomeWindow.h"
#include "Widget_Lib/FuncViewer/FuncViewerWidget.h"
WelcomeWindow::WelcomeWindow(QWidget *parent,QString name):
    BasicWindow(parent,name)
{

}
static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();
    //    ret->registerModel<ImageShowModel>();

    //    ret->registerModel<ImageLoaderModel>();

    //    ret->registerModel<ImageGrayModel>();

    return ret;
}

//创建视频监视窗口
ads::CDockWidget* WelcomeWindow::createDesignWidget()
{
    FuncViewerWidget* aaa = new FuncViewerWidget();
    static int CameraViewerCount = 0;

    DataFlowModel graphModel(registerDataModels());

    QMainWindow mainWin2;
    scene = new DataFlowGraphicsScene(graphModel,mainWin2);
    view = new GraphicsView(scene);
    view->setAcceptDrops(true);
    QGroupBox *groupBox = new QGroupBox("Options");

    QCheckBox *cb1 = new QCheckBox("Nodes are locked");
    QCheckBox *cb2 = new QCheckBox("Connections detachable");
    cb2->setChecked(true);

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(cb1);
    vbl->addWidget(cb2);
    vbl->addStretch();
    groupBox->setLayout(vbl);

    window->addWidget(aaa);
    window->addWidget(view);
    window->setStretchFactor(1, 4);



    QObject::connect(cb1, &QCheckBox::stateChanged, [&graphModel](int state) {
        graphModel.setNodesLocked(state == Qt::Checked);
    });

    QObject::connect(cb2, &QCheckBox::stateChanged, [&graphModel](int state) {
        graphModel.setDetachPossible(state == Qt::Checked);
    });

    auto w = window;
    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(CameraViewerCount++));
    DockWidget->setWidget(w);
    DockWidget->setMinimumSize(100,100);

    DockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidgetMinimumSize);
    return DockWidget;

}

void WelcomeWindow::createContent()
{
    auto DesignerViewer = createDesignWidget();
    this->addDockWidget(ads::LeftDockWidgetArea, DesignerViewer);
//    auto aaa = createEditorWidget();
//    this->addDockWidget(ads::RightDockWidgetArea, aaa);
}
