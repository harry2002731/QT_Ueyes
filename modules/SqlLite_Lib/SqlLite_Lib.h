
#ifndef SQLLITE_LIB_H
#define SQLLITE_LIB_H
#include <Python.h>

#include "SqlLite_Lib_global.h"
#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <Qstring>
#include <QLibrary>
#include <QtPlugin>
#include "SqlInterface.h"
#include <QSqlRelationalTableModel>
#include "QtWidgets/qtableview.h"
#include <QTableWidget>
#include "qpushbutton.h"

class SQLLITE_LIB_EXPORT SqlLite_Lib: public QObject, public DeclareInterface
{

    Q_OBJECT
    Q_INTERFACES(DeclareInterface)
    Q_PLUGIN_METADATA(IID DeclareInterface_iid FILE "qtplugin.json")
public:   
    SqlLite_Lib();
    QSqlDatabase  connectDB(QString db_name); //链接数据库
    void getTableInfo(QSqlDatabase db, QString table_name); //获取表信息
    QWidget* createWidget(int page);
    QWidget* createWidget2(int page);

    QSqlDatabase db ;
    QWidget* big_widget = new QWidget();
    QTableWidget* tableWidget = new QTableWidget;
    int countLineNum();
    void switchPage(int page);
    void switchPage2(int page);

    int currentPage = 0;
    int totalPages = 100; // 假设有 10 页数据
    QString table_name;
    PyObject* pInstanceSvmAnalyzer;
    QString aaa = "Addictive Behavior";

private slots:
    void showPreviousPage();
    void showNextPage();
    void showPreviousPage2();
    void showNextPage2();
    void changeState_triggered2();

};

#endif // SQLLITE_LIB_H
