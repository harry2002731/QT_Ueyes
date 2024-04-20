
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

    QSqlDatabase db ;
    int currentPage = 0; // 当前页码
    int num_each_page = 10; // 每页数据个数
    int totalPages = 10; // 总共的数据页数
    PyObject* pInstanceSvmAnalyzer;
    QString table_name = "非酒精性脂肪肝EC"; //当前查询表的名字
    QWidget* data_visual_widget = new QWidget();
    QTableWidget* tableWidget = new QTableWidget;

    QVector<int> countLineNum(QSqlQuery &query);
    QString searchQueryStatement(QString table_name, QStringList columns, QString target);
    QString paginatedQueryStatement(int num_per_page, int cur_page , QString query_statement);

    void switchPage(int page);
    void getTableInfo(QSqlDatabase db, QString table_name); //获取表信息
    QSqlDatabase  connectDB(QString db_name); //链接数据库
    QWidget* createDataVisualTable(int page);
//    QWidget* createWidget2(int page);
//    void switchPage2(int page);
//    QString aaa = "Addictive Behavior";

private slots:
    void showPreviousPage();
    void showNextPage();
    void onComboBoxChanged(const QString &text);

    //    void showPreviousPage2();
    //    void showNextPage2();
    //    void changeState_triggered2();
    void on_textEdit_textChanged(const QString &text);
    void onComboBoxChanged2(const QString &text);

};

#endif // SQLLITE_LIB_H
