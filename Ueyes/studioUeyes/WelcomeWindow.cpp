#include "WelcomeWindow.h"
#include "Widget_Lib/FuncViewer/FuncViewerWidget.h"
WelcomeWindow::WelcomeWindow(QWidget *parent,QString name):
    BasicWindow(parent,name)
{

}


void WelcomeWindow::createContent()
{
//    auto DesignerViewer = createDesignWidget();
//    this->addDockWidget(ads::LeftDockWidgetArea, DesignerViewer);
    auto aaa = createEditorWidget();
    this->addDockWidget(ads::RightDockWidgetArea, aaa);
}
