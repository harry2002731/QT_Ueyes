#include "sqlLitelib.h"
#include "QtWidgets/qtableview.h"
#include "QtWidgets/qtablewidget.h"
#include "qaction.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include <QFile>
#include <QSqlRelationalDelegate>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QHeaderView>
#include <chrono>
#include <QCompleter>
#include <QSqlRecord>

/*
数据搜索  根据id搜索 ok
可视化
排序 ok
表格美化
当前页码显示 no
界面与sql分离 ok
*/
using namespace std;

SqlLite_Lib::SqlLite_Lib()
{

//    QString last_table_name = "";
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
    else{
        qDebug() << "Database connected";
    }
    model = new QSqlTableModel(this);
//    model2 = new QSqlTableModel(this);
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


// sql对象查询语句
QString SqlLite_Lib::searchQueryStatement(QString table_name, QStringList columns, QString target)
{
    QSqlQuery query;
    QStringList str_list;
    for (const auto column : columns)
    {
        str_list << column + " LIKE '%" + target + "%'";
    }
    QString combinedString = str_list.join(" OR ");
    QString query_statement =  "SELECT * FROM "+table_name+" WHERE ( " + combinedString + ")";

    return query_statement;
}

// sql数据分页查询语句
QString SqlLite_Lib::paginatedQueryStatement(int num_per_page, int cur_page , QString query_statement)
{
    QString offset_value = QString::number(cur_page * num_each_page);
    query_statement += " LIMIT "+ QString::number(num_per_page) +" offset "+ offset_value;
    return query_statement;
}

// sql统计行数查询
QVector<int> SqlLite_Lib::countLineNum(QSqlQuery& query)
{
    query.last();
    int rowCount = query.at() + 1;
    query.first();//重新定位指针到结果集首位

     int columnCount = query.record().count(); // 获取查询结果的列数
    QVector<int> data_size = {rowCount,columnCount};
    return data_size;
}
// Qsql 升序排列
void SqlLite_Lib::ascendTableItem(int column_id)
{
    model->setSort(column_id, Qt::AscendingOrder); //id属性即第0列，升序排列
    model->select();
}
// Qsql 降序排列
void SqlLite_Lib::descendTableItem(int column_id)
{
    model->setSort(column_id, Qt::DescendingOrder); //id属性即第0列，升序排列
    model->select();
}

// Qsql 查询对象
void SqlLite_Lib::searchTableItem(QStringList columns, QString target, bool search_now)
{
    QStringList str_list;
    for (const auto column : columns)
        str_list << column + " LIKE '%" + target + "%'";
    QString combinedString = str_list.join(" OR ");
    if (search_now)
        model->setFilter(combinedString);
    else
        total_search_string<<combinedString;
}

// Qsql 查询非零对象
void SqlLite_Lib::searchNonZeroItem(QStringList columns, QString target , bool search_now)
{
    QStringList str_list;
    for (const auto column : columns)
        str_list << column + " <> 0";
    QString combinedString = str_list.join(" OR ");
    if (search_now)
        model->setFilter(combinedString);
    else
        total_search_string<<combinedString;
}

void SqlLite_Lib::searchTableAccurateItem(QStringList columns, QString target , bool search_now)
{
    QStringList str_list;
    for (const auto column : columns)
        str_list << column + " = " + "'" + target + "'" ;
    QString combinedString = str_list.join(" OR ");
    if (search_now)
        model->setFilter(combinedString);
    else
        total_search_string<<combinedString;
}

void SqlLite_Lib::searchNow(){
    QString combinedString = total_search_string.join(" AND ");
    if (combinedString.length())
    {
        model->setFilter(combinedString);
    }

    else
        qDebug()<<"error!!!!!!!!!!!!";
    total_search_string.clear();

}

void SqlLite_Lib::searchTableMulItem(QStringList columns, QStringList targets)
{
    QStringList str_list;
    for (int i = 0 ; i<columns.size();i++)
        str_list << columns[i] + " = " +"'" +targets[i]+"'" ;
    QString combinedString = str_list.join(" AND ");
    model->setFilter(combinedString);

    qDebug()<<combinedString<<model->rowCount();

}

// QSql 整表查询
QSqlTableModel* SqlLite_Lib::queryEntireTable(QString table_name)
{
    model->setTable(table_name);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select(); //选取整个表的所有行

//    while(model->canFetchMore())
//    {
//        model->fetchMore();
//    }
    return model;
}
//    QStringList columns;
//    columns<<"id"<<"sentence"<<"eng";
//    QSqlQueryModel *model = new QSqlQueryModel;
//    QString seach_query_statement = searchQueryStatement(table_name,columns,search_item);

//    model->setQuery(seach_query_statement);
//    model->setHeaderData(0, Qt::Horizontal, tr("id"));
//    model->setHeaderData(1, Qt::Horizontal, tr("sentence"));
//    model->setHeaderData(1, Qt::Horizontal, tr("eng"));
//    return model;

//    QStringList columns;
//    columns<<"id"<<"sentence"<<"eng";
//    QString seach_query_statement = searchQueryStatement(table_name,columns,search_item);
//    QString paginated_query_statement = paginatedQueryStatement(num_each_page, page , seach_query_statement);

//    QSqlQuery query;
//    query.exec(paginated_query_statement);
//    int line_num = countLineNum(query)[0];
////    totalPages = (line_num + num_each_page - 1) / num_each_page; //获取总页数
//    totalPages =10;

//    int colCount= 3;
//    int rowCount = num_each_page;

//    tableWidget->setColumnCount(colCount);
//    tableWidget->setRowCount(rowCount);
//    QStringList header= QStringList();
//    header<<"患者编号"<<"中文病例"<<"英文病例";
//    tableWidget->setHorizontalHeaderLabels(header);
//    tableWidget->setSortingEnabled(true);  //启动排序

//    for (int row = 0; row < num_each_page; ++row) {
//        if (query.next()) {
//            // 输出每一行数据
//            for (int col = 0; col < 3; ++col) {
//                tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString())); // 将 QTableWidgetItem 添加到 QTableWidget
//            };
//        }
//        else {
//            for (int col = 0; col < 3; ++col) {
//                tableWidget->setItem(row, col, new QTableWidgetItem(QString(""))); // 将 QTableWidgetItem 添加到 QTableWidget
//            };
//        }
//    }


//QSqlTableModel* SqlLite_Lib::queryEntireTable2(QString table_name)
//{
//    model2->setTable(table_name);
//    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model2->select(); //选取整个表的所有行
//    return model2;

//}
//void SqlLite_Lib::on_textEdit_textChanged(const QString &text)
//{
//    QString input_name=text;
//    int row_num=tableWidget->rowCount();
//    if (input_name=="")//判断是否是空，如果是空就显示所有行
//    {
//        for(int i=0;i<row_num;i++)
//        {
//            tableWidget->setRowHidden(i,false);//为false就是显示
//        }
//    }
//    else
//    {
//        //找到符合条件的索引 是通过你输入的和表格里面所有内容进行比对
//        QList <QTableWidgetItem *> item = tableWidget->findItems(text, Qt::MatchContains);
//        //然后把所有行都隐藏
//        for(int i=0;i<row_num;i++)
//        {
//            tableWidget->setRowHidden(i,true);//隐藏

//        }
//        //判断符合条件索引是不是空
//        if(!item.empty())
//        {
//            //恢复对应的行
//            for(int i=0;i<item.count();i++)
//            {
//                tableWidget->setRowHidden(item.at(i)->row(),false);//回复对应的行，也可以回复列
//            }
//        }
//    }

//}


//void SqlLite_Lib::onComboBoxChanged(const QString &text) {
//    // text 是当前选中或输入的文本
//    qDebug() << "Selected or entered text:" << text;
//    table_name = text;
//    currentPage = 0;

//    switchPage(currentPage);

//}

//void SqlLite_Lib::onComboBoxChanged2(const QString &text) {
//    // text 是当前选中或输入的文本
//    qDebug() << "Selected or entered text:" << text;
//    num_each_page = text.toInt();

//    switchPage(currentPage);

//}
//void SqlLite_Lib::showPreviousPage()
//{
//    if (currentPage > 0) {
//        currentPage--;
//        switchPage(currentPage);

//    }
//}

//void SqlLite_Lib::showNextPage()
//{
//    if (currentPage < totalPages - 1) {
//        currentPage++;
//        switchPage(currentPage);
//    }
//}


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
