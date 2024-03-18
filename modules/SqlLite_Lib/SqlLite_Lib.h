#ifndef SQLLITE_LIB_H
#define SQLLITE_LIB_H

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

class SQLLITE_LIB_EXPORT SqlLite_Lib: public QObject, public DeclareInterface
{

    Q_OBJECT
    Q_INTERFACES(DeclareInterface)
    Q_PLUGIN_METADATA(IID DeclareInterface_iid FILE "qtplugin.json")
public:   
    SqlLite_Lib();
    QSqlDatabase  connectDB(QString db_name); //链接数据库
    void getTableInfo(QSqlDatabase db, QString table_name); //获取表信息
    QTableWidget* createWidget();
    QSqlDatabase db ;
};

#endif // SQLLITE_LIB_H
