#include <Python.h>

#include "SqlLite_Lib.h"
#include "QtWidgets/qtableview.h"
#include "QtWidgets/qtablewidget.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include <QFile>
#include <QSqlRelationalDelegate>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QHeaderView>

SqlLite_Lib::SqlLite_Lib()
{

    table_name = "非酒精性脂肪肝EC";


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
    if (query.exec("PRAGMA table_info(非酒精性脂肪肝EC);")) {
        // 逐行获取查询结果
        while (query.next()) {
            // 获取数据
            QString name = query.value(0).toString(); // 获取第一个字段（name）的值
            QString age = query.value(1).toString(); // 获取第二个字段（age）的值
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}

QWidget* SqlLite_Lib::createWidget(int page)
{
    QVBoxLayout *layout = new QVBoxLayout();
    QPushButton *prevButton = new QPushButton("Previous", tableWidget);
    QPushButton *nextButton = new QPushButton("Next", tableWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(prevButton);
    buttonLayout->addStretch(); // 弹性空间，用于分隔按钮
    buttonLayout->addWidget(nextButton);

    layout->addWidget(tableWidget);
    layout->addLayout(buttonLayout);
    big_widget->setLayout(layout);
    connect(prevButton, &QPushButton::clicked, this, &SqlLite_Lib::showPreviousPage);
    connect(nextButton, &QPushButton::clicked, this, &SqlLite_Lib::showNextPage);

    // 设置表格伸展策略为 Expanding
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    switchPage(page);
    return big_widget;
}
void SqlLite_Lib::switchPage(int page)
{
    int pageSize = 30;
    QString strValue = QString::number(page*pageSize);
    totalPages = (countLineNum() + 30 - 1) / 30; //获取总页数
    QSqlQuery query;
    query.exec("SELECT * FROM 非酒精性脂肪肝EC LIMIT 30 offset "+ strValue); // 查询表 a 的前十行数据

    static int colCount= 3;
    static int rowCount = pageSize;

    tableWidget->setColumnCount(colCount);
    tableWidget->setRowCount(rowCount);

    for (int row = 0; row < 30; ++row) {
        if (query.next()) {
            // 输出每一行数据
            for (int col = 0; col < 3; ++col) {
                tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString())); // 将 QTableWidgetItem 添加到 QTableWidget
            };
        }
        else {
            for (int col = 0; col < 3; ++col) {
                tableWidget->setItem(row, col, new QTableWidgetItem(QString(""))); // 将 QTableWidgetItem 添加到 QTableWidget
            };
        }
    }
}
//统计行数
int SqlLite_Lib::countLineNum()
{
    int lineNum = -1;
    QSqlQuery query("SELECT COUNT(*) FROM " + table_name);
    if (query.next()) {
        lineNum = query.value(0).toInt();
    }
    return lineNum;
}

void SqlLite_Lib::showPreviousPage()
{
    if (currentPage > 0) {
        currentPage--;
        switchPage(currentPage);
    }
}

void SqlLite_Lib::showNextPage()
{
    if (currentPage < totalPages - 1) {
        currentPage++;
        switchPage(currentPage);
    }
}

