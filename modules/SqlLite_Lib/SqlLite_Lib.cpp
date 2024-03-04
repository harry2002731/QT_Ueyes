#include "SqlLite_Lib.h"
#include <QFile>

SqlLite_Lib::SqlLite_Lib()
{
}

QSqlDatabase SqlLite_Lib::connectDB(QString db_name)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //设置数据库类型
    QFile dbFile(db_name);
    db.setDatabaseName(dbFile.fileName());
    if (!db.open())
    {
        qDebug() << "Database unconnected";
        throw std::runtime_error("Failed to open database connection!");
    }
    return db;


}

void SqlLite_Lib::getTableInfo(QSqlDatabase db, QString table_name)
{
    QSqlQuery query;
    if (query.exec("PRAGMA table_info(EC);")) {
        // 逐行获取查询结果
        while (query.next()) {
            // 获取数据
            QString name = query.value(0).toString(); // 获取第一个字段（name）的值
            QString age = query.value(1).toString(); // 获取第二个字段（age）的值
            qDebug() << "Name: " << name << ", Age: " << age;

        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}
