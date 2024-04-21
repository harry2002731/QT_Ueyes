#ifndef SQLINTERFACE_H
#define SQLINTERFACE_H

#include <QTableWidget>
#include "qsqltablemodel.h"

#include "QtWidgets/qtableview.h"
#include "qsqldatabase.h"
#include "qsqlquerymodel.h"
#define DeclareInterface_iid "Examples.Plugin.DeclareInterface"

//定义接口
#include "qglobal.h"
class DeclareInterface
{
public:
    virtual ~DeclareInterface() {}
    virtual QSqlDatabase connectDB(QString db_name) = 0;
    virtual void getTableInfo(QSqlDatabase db, QString table_name) = 0;
    virtual void descendTableItem(int column_id) = 0;
    virtual void ascendTableItem(int column_id) = 0;
    virtual void searchTableItem(QStringList columns, QString target) = 0;
    virtual QSqlTableModel* queryEntireTable(QString table_name) = 0;

};

//一定是唯一的标识符

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(DeclareInterface,DeclareInterface_iid)
QT_END_NAMESPACE


#endif // SQLINTERFACE_H
