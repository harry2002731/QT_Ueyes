#include "DesignWindow.h"
#include "ImageGrayModel.h"
#include "ImageLoaderModel.hpp"
#include "ImageShowModel.hpp"
#include "Widget_Lib/FuncViewer/FuncViewerWidget.h"
#include "Camera_Lib/Basler_Lib/Basler_Lib.h"
#include "qthread.h"
#include "qtimer.h"

DesignWindow::DesignWindow(QWidget *parent,QString name):
    BasicWindow(parent,name)
{
//    QThread *thread = new QThread();
//    // 将任务对象移动到新线程
//    myTask->moveToThread(thread);

    // 当线程启动时，执行任务的 run 方法
//    QObject::connect(thread, &QThread::started, myTask, &Basler_Lib::readImage);
//    thread->start();

}
static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();

        ret->registerModel<ImageShowModel>();

        ret->registerModel<ImageLoaderModel>();

        ret->registerModel<ImageGrayModel>();

    return ret;
}
ads::CDockWidget* DesignWindow::createDesignWidget()
{
    FuncViewerWidget* aaa = new FuncViewerWidget();
    static int CameraViewerCount = 0;

    static DataFlowModel graphModel(registerDataModels());

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



//    QObject::connect(cb1, &QCheckBox::stateChanged, [&graphModel](int state) {
//        graphModel.setNodesLocked(state == Qt::Checked);
//    });

//    QObject::connect(cb2, &QCheckBox::stateChanged, [&graphModel](int state) {
//        graphModel.setDetachPossible(state == Qt::Checked);
//    });

    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(CameraViewerCount++));
    DockWidget->setWidget(m_window);
    DockWidget->setMinimumSize(100,100);

    DockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidgetMinimumSize);
    return DockWidget;

}


void DesignWindow::createContent()
{
    auto  cameraViewer = createCameraViewerWidget();
    this->addDockWidgetFloating( cameraViewer);
    auto DesignerViewer = createDesignWidget();
    this->addDockWidget(ads::LeftDockWidgetArea, DesignerViewer);
    auto aaa = createEditorWidget();
    this->addDockWidget(ads::RightDockWidgetArea, aaa);
}

