#ifndef FUNCVIEWERWIDGET_H
#define FUNCVIEWERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include "Widget_Lib_global.h"
#include "qboxlayout.h"
#include <QScrollArea>
#include <QSettings>
#include <QFileInfo>
#include <QMessageBox>

namespace Ui {
class FuncViewerWidget;
}


//列表窗体
class WIDGET_LIB_EXPORT FuncViewerWidget : public QWidget
{
    Q_OBJECT
public:
    FuncViewerWidget();
    void initWidget();
    void readWidgetConfig();
    void makePageWidget();
    void addWidget(QString title,QWidget *widget);
    Ui::FuncViewerWidget *ui;
    ~FuncViewerWidget();
    QVBoxLayout *m_pContentVBoxLayout;

};


extern "C" /*Important for avoiding Name decoration*/
{
WIDGET_LIB_EXPORT FuncViewerWidget* __cdecl  CreateWidget();
};

#endif // FUNCVIEWERWIDGET_H




