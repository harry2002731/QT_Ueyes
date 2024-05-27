#ifndef TESTINTERFACE_H
#define TESTINTERFACE_H
#include <QtPlugin>
#include <QtCore>
#include "qglobal.h"
#define TestInterface1_iid "Examples.Plugin.TestInterface"
#include <QSqlDatabase>
#include "qsqltablemodel.h"


class TestInterface
{
public:
    virtual ~TestInterface() {}
    virtual QSqlDatabase connectDB(QString db_name) = 0;
    virtual void getTableInfo(QSqlDatabase db, QString table_name) = 0;
    virtual void descendTableItem(int column_id) = 0;
    virtual void ascendTableItem(int column_id) = 0;
    virtual void searchTableItem(QStringList columns, QString target, bool search_now = false) = 0;
    virtual void searchNonZeroItem(QStringList columns, QString target, bool search_now = false) = 0;
    virtual void searchTableAccurateItem(QStringList columns, QString target, bool search_now = false) = 0;
    virtual void searchTableMulItem(QStringList columns, QStringList targets) = 0;
    virtual void searchNow() = 0;
    virtual QSqlTableModel* queryEntireTable(QString table_name) = 0;
    //    virtual QSqlTableModel* queryEntireTable2(QString table_name) = 0;
    //    virtual ~TestInterface() ;

};

//QT_BEGIN_NAMESPACE
//Q_DECLARE_INTERFACE(TestInterface,TestInterface1_iid)
//QT_END_NAMESPACE


#define SQLITESTUDIO_PLUGIN(file)\
Q_PLUGIN_METADATA(IID TestInterface1_iid FILE file) \
    Q_INTERFACES(TestInterface)

Q_DECLARE_INTERFACE(TestInterface, TestInterface1_iid)


#endif // TESTINTERFACE_H
