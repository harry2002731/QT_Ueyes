#include "SqlLite_Lib.h"
#include "QtWidgets/qtableview.h"
#include "QtWidgets/qtablewidget.h"
#include "qaction.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include <QFile>
#include <QSqlRelationalDelegate>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QHeaderView>
#include <chrono>
#include <QCompleter>

using namespace std;

SqlLite_Lib::SqlLite_Lib()
{
    table_name = "非酒精性脂肪肝EC";
//    Py_Initialize();


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
    if (query.exec("PRAGMA table_info("+table_name+")")) {
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

QWidget* SqlLite_Lib::createDataVisualTable(int page)
{
    // 设置表格伸展策略为 Expanding
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    QVBoxLayout *layout = new QVBoxLayout();
    QPushButton *prevButton = new QPushButton("Previous", tableWidget);
    QPushButton *nextButton = new QPushButton("Next", tableWidget);
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    QComboBox *pageBox = new QComboBox();
    QStringList num_each_page;
    num_each_page << "10"<< "20"<< "30"<< "40"<< "50";
    pageBox->addItems(num_each_page);

    bottomLayout->addWidget(prevButton);
    bottomLayout->addStretch(); // 弹性空间，用于分隔按钮
    bottomLayout->addWidget(pageBox);
    bottomLayout->addStretch(); // 弹性空间，用于分隔按钮
    bottomLayout->addWidget(nextButton);


    QComboBox *diseaseBox = new QComboBox();
    QStringList diseases;
    diseases << "非酒精性脂肪肝EC"<< "非酒精性脂肪肝IC"<< "非酒精脂肪肝炎EC"<< "非酒精脂肪肝炎IC"<< "肝硬化IC"<< "肝硬化EC";
    diseaseBox->addItems(diseases);


    connect(prevButton, &QPushButton::clicked, this, &SqlLite_Lib::showPreviousPage);
    connect(nextButton, &QPushButton::clicked, this, &SqlLite_Lib::showNextPage);
    connect(pageBox,&QComboBox::currentTextChanged,this,&SqlLite_Lib::onComboBoxChanged2);
    connect(diseaseBox,&QComboBox::currentTextChanged,this,&SqlLite_Lib::onComboBoxChanged);


    data_visual_widget->setLayout(layout);
    layout->addWidget(diseaseBox);
    layout->addWidget(tableWidget);
    layout->addLayout(bottomLayout);

    switchPage(page);
    return data_visual_widget;
}
void SqlLite_Lib::switchPage(int page)
{
    QString strValue = QString::number(page * num_each_page);
    totalPages = (countLineNum() + num_each_page - 1) / num_each_page; //获取总页数
    QSqlQuery query;
    query.exec("SELECT * FROM "+table_name+" LIMIT "+ QString::number(num_each_page) +" offset "+ strValue); // 查询表 a 的前十行数据

    int colCount= 3;
    int rowCount = num_each_page;

    tableWidget->setColumnCount(colCount);
    tableWidget->setRowCount(rowCount);

    for (int row = 0; row < num_each_page; ++row) {
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
void SqlLite_Lib::onComboBoxChanged(const QString &text) {
    // text 是当前选中或输入的文本
    qDebug() << "Selected or entered text:" << text;
    table_name = text;
    currentPage = 0;

    switchPage(currentPage);

}

void SqlLite_Lib::onComboBoxChanged2(const QString &text) {
    // text 是当前选中或输入的文本
    qDebug() << "Selected or entered text:" << text;
    num_each_page = text.toInt();

    switchPage(currentPage);

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


//QWidget* SqlLite_Lib::createWidget2(int page)
//{
//    QVBoxLayout *layout = new QVBoxLayout();
//    QPushButton *prevButton = new QPushButton("Previous", tableWidget);
//    QPushButton *nextButton = new QPushButton("Next", tableWidget);
//    QHBoxLayout *buttonLayout = new QHBoxLayout();
//    buttonLayout->addWidget(prevButton);
//    buttonLayout->addStretch(); // 弹性空间，用于分隔按钮
//    buttonLayout->addWidget(nextButton);


//    data_visual_widget->setLayout(layout);
//    connect(prevButton, &QPushButton::clicked, this, &SqlLite_Lib::showPreviousPage);
//    connect(nextButton, &QPushButton::clicked, this, &SqlLite_Lib::showNextPage);


//    QHBoxLayout *layout2 = new QHBoxLayout();
//    layout2->setAlignment(Qt::AlignTop);

//    // 创建按钮并添加到布局中
//    for (char letter = 'A'; letter <= 'D'; ++letter) {
//        QPushButton *button = new QPushButton(QString(letter));
//        connect(button,&QPushButton::clicked, this, &SqlLite_Lib::changeState_triggered2);
//        layout2->addWidget(button);
//    }
//    layout->addLayout(layout2);
//    layout->addWidget(tableWidget);
//    layout->addLayout(buttonLayout);

//    // 设置表格伸展策略为 Expanding
//    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    switchPage2(page);



//    return data_visual_widget;
//}
//void SqlLite_Lib::switchPage2(int page)
//{

//    PyRun_SimpleString("import sys");
//    std::string path = "sys.path.append(\"D:/Projects/PythonProjects/Medical_Classification/models/SVM/\")";
//    totalPages = (10 + 30 - 1) / 30; //获取总页数

//    const char* cstr_cmd = path.c_str();
//    PyRun_SimpleString(cstr_cmd);
//    PyObject* pModule = PyImport_ImportModule("svm_test"); //模块名，不是文件名
//    PyObject* pDict = PyModule_GetDict(pModule); //获得Python模块中的函数列

//    //获取python类
//    PyObject* pSvmAnalyzer = PyDict_GetItemString(pDict, "SvmAnalyzer");//获取函数字典中的YOLO类
//    pInstanceSvmAnalyzer = PyObject_CallObject(pSvmAnalyzer,NULL);

//    auto start = std::chrono::high_resolution_clock::now();

//    PyObject *str = PyUnicode_FromString(aaa.toStdString().c_str());
//    cout << "Can't find YOLO instance!" << endl;

//    PyObject* pValue = PyObject_CallMethod(pInstanceSvmAnalyzer, "get_suggestion","(Oi)",str,10);//pInstanceSvmAnalyzer对应self，ArgArray
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    std::cout << "Duration: " << duration.count() << " ms" << std::endl;

//    QVector<QPair<QVariant, QVariant>> array2D;
//    Py_ssize_t rows = PySequence_Size(pValue);
//    for (Py_ssize_t i = 0; i < rows; ++i) {
//        PyObject* row = PySequence_GetItem(pValue, i);
//        if (!row) {
//            PyErr_Print();
//            continue;
//        }

//        // 获取每行的列数
//        Py_ssize_t cols = PySequence_Size(row);
//        float floatValue=0;
//        string stringValue="";
//        for (Py_ssize_t j = 0; j < cols; ++j) {
//            PyObject* item = PySequence_GetItem(row, j);
//            if (!item) {
//                PyErr_Print();
//                continue;
//            }
//            // 根据元素的类型进行处理
//            if (PyFloat_Check(item)) {
//                // 如果是整数类型
//                floatValue = PyFloat_AsDouble(item);
////                std::cout << "floatValue: " << floatValue << " ";
//            }
//            else if (PyUnicode_Check(item)) {
//                // 如果是字符串类型
//                PyObject* str = PyUnicode_AsEncodedString(item, "GBK", "strict");
//                stringValue = PyBytes_AS_STRING(str);
//                stringValue  = QString::fromLocal8Bit(stringValue.data()).toUtf8().data();

////                std::cout << "String: " << stringValue << " ";
//                Py_DECREF(str);
//            }
//            else {
//                // 如果是其他类型，可以添加更多的条件分支来处理
//                std::cout << "Unknown type" << " ";
//            }
//            Py_DECREF(item);
//        }
//        if (floatValue && stringValue!="")
//        {
//            array2D.append(qMakePair<QString, double>(QString::fromStdString(stringValue), floatValue));

//        }
//        Py_DECREF(row);
//    }


//    int pageSize = 30;
//    QString strValue = QString::number(page*pageSize);
//    totalPages = (countLineNum() + 30 - 1) / 30; //获取总页数
////    QSqlQuery query;
////    query.exec("SELECT * FROM 非酒精性脂肪肝EC LIMIT 30 offset "+ strValue); // 查询表 a 的前十行数据

//        static int colCount= 3;
//    static int rowCount = pageSize;

//    tableWidget->setColumnCount(colCount);
//    tableWidget->setRowCount(rowCount);

//    for (int i = 0; i < array2D.size(); ++i) {
//        const QPair<QVariant, QVariant> &pair = array2D.at(i);
//        // 从 pair 中获取第一个和第二个 QVariant 对象
//        QVariant firstVariant = pair.first;
//        QVariant secondVariant = pair.second;

//        // 根据需要将 QVariant 转换为适当的类型
//        // 例如，如果我们知道第一个是字符串，第二个是整数
//        QString firstString = firstVariant.toString(); // 将第一个 QVariant 转换为 QString
//        double secondInt = secondVariant.toDouble(); // 将第二个 QVariant 转换为 int
//        tableWidget->setItem(i, 0, new QTableWidgetItem(firstString)); // 将 QTableWidgetItem 添加到 QTableWidget
//        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(secondInt, 'f', 6))); // 将 QTableWidgetItem 添加到 QTableWidget

//        // 打印结果
////        std::cout << "String: " << firstString.toStdString() << ", Int: " << secondInt << std::endl;
//    }
//}

//void SqlLite_Lib::showPreviousPage2()
//{
//    if (currentPage > 0) {
//        currentPage--;
//        switchPage(currentPage);
//    }
//}

//void SqlLite_Lib::showNextPage2()
//{
//    if (currentPage < totalPages - 1) {
//        currentPage++;
//        switchPage(currentPage);
//    }
//}

//void SqlLite_Lib::changeState_triggered2()
//{
//    QPushButton *btn = qobject_cast<QPushButton*>(sender());

//    QString name =  btn->text();
//    if (name == "A") {

//        aaa = "Addictive Behavior";
//        switchPage2(currentPage);

//    }
//    else if (name == "B") {

//        aaa = "Age";
//        switchPage2(currentPage);


//    }
//    else if (name == "C") {
//        aaa = "Allergy Intolerance";
//        switchPage2(currentPage);

//    }
//}
