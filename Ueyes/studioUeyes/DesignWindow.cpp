#include "DesignWindow.h"
#include "Widget_Lib/FuncViewer/FuncViewerWidget.h"

DesignWindow::DesignWindow(QWidget *parent,QString name):
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
ads::CDockWidget* DesignWindow::createDesignWidget()
{
    FuncViewerWidget* aaa = new FuncViewerWidget();
    static int CameraViewerCount = 0;

    DataFlowModel graphModel(registerDataModels());

    QMainWindow mainWin2;
    m_scene = new DataFlowGraphicsScene(graphModel,mainWin2);
    m_view = new GraphicsView(m_scene);
    m_view->setAcceptDrops(true);
    QGroupBox *groupBox = new QGroupBox("Options");

    QCheckBox *cb1 = new QCheckBox("Nodes are locked");
    QCheckBox *cb2 = new QCheckBox("Connections detachable");
    cb2->setChecked(true);

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(cb1);
    vbl->addWidget(cb2);
    vbl->addStretch();
    groupBox->setLayout(vbl);

    m_window->addWidget(aaa);
    m_window->addWidget(m_view);
    m_window->setStretchFactor(1, 4);



    QObject::connect(cb1, &QCheckBox::stateChanged, [&graphModel](int state) {
        graphModel.setNodesLocked(state == Qt::Checked);
    });

    QObject::connect(cb2, &QCheckBox::stateChanged, [&graphModel](int state) {
        graphModel.setDetachPossible(state == Qt::Checked);
    });

    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(CameraViewerCount++));
    DockWidget->setWidget(m_window);
    DockWidget->setMinimumSize(100,100);

    DockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidgetMinimumSize);
    return DockWidget;

}


void DesignWindow::createContent()
{
    auto  cameraViewer = createCameraViewerWidget();
    this->addDockWidget(ads::RightDockWidgetArea, cameraViewer);
    auto DesignerViewer = createDesignWidget();
    this->addDockWidget(ads::LeftDockWidgetArea, DesignerViewer);
    auto aaa = createEditorWidget();
    this->addDockWidget(ads::RightDockWidgetArea, aaa);
}

