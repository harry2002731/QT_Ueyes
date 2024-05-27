
#ifndef SQLLITELIB_H
#define SQLLITELIB_H
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
#include "qsqltablemodel.h"

class SQLLITE_LIB_EXPORT SqlLite_Lib: public DeclareInterface
{

   Q_OBJECT
    Q_INTERFACES(DeclareInterface)
    Q_PLUGIN_METADATA(IID DeclareInterface_iid FILE "qtplugin.json")

//    SQLITESTUDIO_PLUGIN("qtplugin.json")

public:   
    SqlLite_Lib();

    QSqlDatabase db ;
    int currentPage = 0; // 当前页码
    int num_each_page = 10; // 每页数据个数
    int totalPages = 10; // 总共的数据页数z
    QSqlTableModel * model;

    QVector<int> countLineNum(QSqlQuery &query);
    QString searchQueryStatement(QString table_name, QStringList columns, QString target);
    QString paginatedQueryStatement(int num_per_page, int cur_page , QString query_statement);

    void getTableInfo(QSqlDatabase db, QString table_name); //获取表信息
    QSqlDatabase  connectDB(QString db_name); //链接数据库

    void searchNow();
    void descendTableItem(int column_id);
    void ascendTableItem(int column_id);
    void searchTableItem(QStringList columns, QString target, bool search_now = false);
    void searchNonZeroItem(QStringList columns, QString target, bool search_now = false);
    void searchTableAccurateItem(QStringList columns, QString target, bool search_now = false);
    QSqlTableModel* queryEntireTable(QString table_name);
//    QSqlTableModel* queryEntireTable2(QString table_name);
    void searchTableMulItem(QStringList columns, QStringList targets);
    QStringList total_search_string;



private slots:

};

#endif // SQLLITELIB_H
