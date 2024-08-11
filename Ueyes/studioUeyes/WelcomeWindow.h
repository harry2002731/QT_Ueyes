#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H
#include <BasicWindow.h>
#include <QString>
#include <QWidget>

#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include "DataFlowModel.h"
#include "qboxlayout.h"
#include "qcheckbox.h"
#include "qgroupbox.h"
#include <QSplitter>

using QtNodes::ConnectionStyle;
using QtNodes::DataFlowGraphicsScene;
using QtNodes::DataFlowGraphModel;
using QtNodes::GraphicsView;
using QtNodes::NodeDelegateModelRegistry;
class WelcomeWindow : public BasicWindow
{
    Q_OBJECT
public:
    WelcomeWindow(QWidget *parent,QString name);
    void createContent() override;
    virtual ads::CDockWidget* createDesignWidget();
    DataFlowGraphicsScene *scene;
    GraphicsView  *view;
    QSplitter * window = new QSplitter(Qt::Horizontal);


};

#endif // WELCOMEWINDOW_H
