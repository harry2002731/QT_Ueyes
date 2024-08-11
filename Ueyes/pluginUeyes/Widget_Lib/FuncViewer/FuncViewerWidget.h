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
#include "BaseWidget.h"
#include "qlistwidget.h"

namespace Ui {
class FuncViewerWidget;
}


//列表窗体
class WIDGET_LIB_EXPORT FuncViewerWidget : public QWidget
{
    Q_OBJECT
public:
    FuncViewerWidget();
    ~FuncViewerWidget();

    Ui::FuncViewerWidget *ui;
    QVBoxLayout *m_pContentVBoxLayout;
    QString aaa;

    void initWidget(); //初始化主窗体
    void readWidgetConfig(); //读取窗体配置
    void makePageWidget(); //配置主窗体内的子窗体
    void addPageWidget(QString title,QWidget *widget);//添加子窗体到主窗体中
    QPushButton * bbb;
    QPushButton * ccc;
    QWidget *m_widget = new QWidget();
    void mouseMoveEvent(QMouseEvent *event);

signals:

};

//用来在显示调用动态库时候调用类，额外增加
extern "C"
{
WIDGET_LIB_EXPORT FuncViewerWidget* __cdecl  CreateWidget();
};

//WIDGET_LIB_EXPORT FuncViewerWidget*  CreateWidget();


#endif // FUNCVIEWERWIDGET_H




