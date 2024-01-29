#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow(QWidget *parent,QString name):
    BasicWindow(parent,name)
{

}

void WelcomeWindow::createContent()
{
    auto CameraViewer = createCameraViewerWidget();
    this->addDockWidget(ads::LeftDockWidgetArea, CameraViewer);
    auto aaa = createEditorWidget();
    this->addDockWidget(ads::RightDockWidgetArea, aaa);
}
