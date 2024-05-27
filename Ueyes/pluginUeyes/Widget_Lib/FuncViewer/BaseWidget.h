#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);

//    virtual void initWidget(); //初始化主窗体
//    virtual void readWidgetConfig(); //读取窗体配置
//    virtual void makePageWidget(); //配置主窗体内的子窗体
//    virtual void addPageWidget(QString title,QWidget *widget);//添加子窗体到主窗体中

signals:

};

#endif // BASEWIDGET_H
