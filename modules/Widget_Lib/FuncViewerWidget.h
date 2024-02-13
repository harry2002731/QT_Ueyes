#ifndef FUNCVIEWERWIDGET_H
#define FUNCVIEWERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include "Widget_Lib_global.h"
#include "qboxlayout.h"



namespace Ui {
class FuncViewerWidget;
}


//列表窗体
class WIDGET_LIB_EXPORT FuncViewerWidget : public QWidget
{
    Q_OBJECT
public:
    FuncViewerWidget();
    void addWidget(QString title,QWidget *widget);
    Ui::FuncViewerWidget *ui;
    ~FuncViewerWidget();
    QVBoxLayout *m_pContentVBoxLayout;

};

#endif // FUNCVIEWERWIDGET_H




