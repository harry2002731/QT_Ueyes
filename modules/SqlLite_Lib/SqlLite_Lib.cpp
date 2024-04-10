#include <Python.h>

#include "SqlLite_Lib.h"
#include "QtWidgets/qtableview.h"
#include "QtWidgets/qtablewidget.h"
#include <QFile>
#include <QSqlRelationalDelegate>
#include <QStandardItemModel>
#include <QTableWidget>

SqlLite_Lib::SqlLite_Lib()
{
}

QSqlDatabase SqlLite_Lib::connectDB(QString db_name)
{
    db = QSqlDatabase::addDatabase("QSQLITE"); //设置数据库类型
    QFile dbFile(db_name);
    QSqlQuery query;

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

QTableWidget* SqlLite_Lib::createWidget()
{
    QSqlRelationalTableModel* model = new QSqlRelationalTableModel();

    model->setTable("EC");
//    model->setRelation(0, QSqlRelation("id", "EC", "exclusion_criteria"));
    model->select();
//    view->setItemDelegate(new QSqlRelationalDelegate(view));

    auto tableWidget = new QTableWidget;
    static int colCount = 30;
    static int rowCount = 30;
    tableWidget->setColumnCount(colCount);
    tableWidget->setRowCount(rowCount);


    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QModelIndex index = model->index(row, col); // 获取 QModelIndex
            QVariant data = model->data(index, Qt::DisplayRole); // 获取数据

            QTableWidgetItem* item = new QTableWidgetItem(data.toString()); // 创建 QTableWidgetItem
            tableWidget->setItem(row, col, item); // 将 QTableWidgetItem 添加到 QTableWidget
        }
    }
//    Py_Initialize(); //初始化python模块
//    if ( !Py_IsInitialized() )//查看是否成功初始化
//    {
//    qDebug()<<"failed";
//    }

    return tableWidget;
}
