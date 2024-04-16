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
using namespace std;

SqlLite_Lib::SqlLite_Lib()
{
    table_name = "非酒精性脂肪肝EC";
    Py_Initialize();
    PyRun_SimpleString("import sys");
    std::string path = "sys.path.append(\"D:/Projects/PythonProjects/Medical_Classification/models/SVM/\")";

    const char* cstr_cmd = path.c_str();
    PyRun_SimpleString(cstr_cmd);
    PyObject* pModule = PyImport_ImportModule("svm_test"); //模块名，不是文件名


    if (!pModule) // 加载模块失败
    {
        std::cout << "[ERROR] Python get module failed." << std::endl;
    }
    std::cout << "[INFO] Python get module succeed." << std::endl;


    PyObject* pv = PyObject_GetAttrString(pModule, "aaa");
    if (!pv || !PyCallable_Check(pv))
    {
        std::cout << "[ERROR] Can't find funftion." << endl;
    }
    cout << "[INFO] Get function succeed." << endl;

    PyObject* pValue = PyObject_CallObject(pv, NULL);
    Py_ssize_t rows = PySequence_Size(pValue);
    for (Py_ssize_t i = 0; i < rows; ++i) {
        PyObject* row = PySequence_GetItem(pValue, i);
        if (!row) {
            PyErr_Print();
            continue;
        }

        // 获取每行的列数
        Py_ssize_t cols = PySequence_Size(row);
        for (Py_ssize_t j = 0; j < cols; ++j) {
            PyObject* item = PySequence_GetItem(row, j);
            if (!item) {
                PyErr_Print();
                continue;
            }

            // 根据元素的类型进行处理
            if (PyLong_Check(item)) {
                // 如果是整数类型
                long intValue = PyLong_AsLong(item);
                std::cout << "Integer: " << intValue << " ";
            }
            else if (PyUnicode_Check(item)) {
                // 如果是字符串类型
                PyObject* str = PyUnicode_AsEncodedString(item, "GBK", "strict");
                auto a = PyBytes_AS_STRING(str);
                std::cout << "String111: " << a << " ";
                Py_DECREF(str);
            }
            else {
                // 如果是其他类型，可以添加更多的条件分支来处理
                std::cout << "Unknown type" << " ";
            }

            Py_DECREF(item);
        }
        std::cout << std::endl;

        Py_DECREF(row);
    }

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

