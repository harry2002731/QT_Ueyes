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
#include "qlabel.h"
#include "qlistwidget.h"
#include "qdrag.h"
#include "qevent.h"
#include "qlistwidget.h"
#include "qmimedata.h"
#include "qpainter.h"

namespace Ui {
class FuncViewerWidget;
}

class DraggableLabel : public QLabel {
    Q_OBJECT

public:
    QString title_name;
    explicit DraggableLabel(const QString& text, QWidget* parent = nullptr)
        : QLabel(text, parent) {
        title_name = text;
        setAlignment(Qt::AlignCenter);
        setStyleSheet("background-color: lightgrey; border: 1px solid black;");
        setFixedSize(100, 50);
    }

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            QDrag* drag = new QDrag(this);
            QMimeData* mimeData = new QMimeData;
            drag->exec(Qt::CopyAction|Qt::MoveAction);
            mimeData->setText(title_name);
            drag->setMimeData(mimeData);
            drag->exec(Qt::MoveAction);
        }
    }
};

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
    DraggableLabel* createLabel(const QString& text) ;

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

//用来在显式调用动态库时候调用类，额外增加
extern "C"
{
WIDGET_LIB_EXPORT FuncViewerWidget* __cdecl  CreateWidget();
};

//WIDGET_LIB_EXPORT FuncViewerWidget*  CreateWidget();


#endif // FUNCVIEWERWIDGET_H




