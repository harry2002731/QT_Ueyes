#ifndef SQLLITE_LIB_H
#define SQLLITE_LIB_H

#include "SqlLite_Lib_global.h"
#include <iostream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <Qstring>
#include <QLibrary>
class SQLLITE_LIB_EXPORT SqlLite_Lib
{
public:
    SqlLite_Lib();
    QSqlDatabase  connectDB(QString db_name); //链接数据库
    void getTableInfo(QSqlDatabase db, QString table_name);
};

#endif // SQLLITE_LIB_H
