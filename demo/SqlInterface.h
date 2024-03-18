#ifndef SQLINTERFACE_H
#define SQLINTERFACE_H


#include <QSqlDatabase>
#define DeclareInterface_iid "Examples.Plugin.DeclareInterface"
#include "QtWidgets/qtableview.h"
#include <QTableWidget>

//定义接口
#include "qglobal.h"
class DeclareInterface
{
public:
    virtual ~DeclareInterface() {}
    virtual QSqlDatabase connectDB(QString db_name) = 0;
    virtual void getTableInfo(QSqlDatabase db, QString table_name) = 0;
    virtual QTableWidget* createWidget() = 0;

};

//一定是唯一的标识符

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(DeclareInterface,DeclareInterface_iid)
QT_END_NAMESPACE


#endif // SQLINTERFACE_H
