#ifndef DESIGNWINDOW_H
#define DESIGNWINDOW_H

#include "BasicWindow.h"
#include "DataFlowModel.h"
#include "Widget_Lib/FuncViewer/FuncViewerWidget.h"

#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QSplitter>
#include <QBoxLayout>
#include <QCheckBox>
#include <QGroupBox>

using QtNodes::ConnectionStyle;
using QtNodes::DataFlowGraphicsScene;
using QtNodes::DataFlowGraphModel;
using QtNodes::GraphicsView;
using QtNodes::NodeDelegateModelRegistry;

class DesignWindow: public BasicWindow
{
    Q_OBJECT
public:
    DesignWindow(QWidget *parent,QString name);
    void createContent() override;
    virtual ads::CDockWidget* createDesignWidget();

private:
    QSplitter * m_window = new QSplitter(Qt::Horizontal);
    GraphicsView  *m_view;
    DataFlowGraphicsScene *m_scene;
};

#endif // DESIGNWINDOW_H
