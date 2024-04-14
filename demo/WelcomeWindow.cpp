#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow(QWidget *parent,QString name):
    BasicWindow(parent,name)
{

}

//创建视频监视窗口
ads::CDockWidget* WelcomeWindow::createLoginWidget()
{
    static int CameraViewerCount = 0;
    auto w = new VideoPanel();
    ads::CDockWidget* DockWidget = new ads::CDockWidget(QString("Table %1").arg(CameraViewerCount++));
    DockWidget->setWidget(w);
    DockWidget->setMinimumSize(100,100);

    DockWidget->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromDockWidgetMinimumSize);
    return DockWidget;
}

void WelcomeWindow::createContent()
{
    auto CameraViewer = createCameraViewerWidget();
    this->addDockWidget(ads::LeftDockWidgetArea, CameraViewer);
    auto aaa = createEditorWidget();
    this->addDockWidget(ads::RightDockWidgetArea, aaa);
}
