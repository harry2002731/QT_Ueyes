#include "datatableviewer.h"
#include "qidentityproxymodel.h"
#include "qmenu.h"
#include "qsqlerror.h"
#include "qsqlquerymodel.h"
#include "qstandarditemmodel.h"
#include "ui_DataTableViewer.h"
#include <QMessageBox>

DataTableViewer::DataTableViewer():
    ui(new Ui::DataTableViewer1)
{
    ui->setupUi(this);
    int cur_Page = 0; // 当前页数
    int num_each_page = 10; // 每页数据个数
    int total_pages = 10; // 总共的数据页数
    QString cur_table_name = "非酒精性脂肪肝EC"; //当前查询表的名字
    QString search_item="";
    this->initWidget();
}


void DataTableViewer::initWidget()
{
    // 设置表格伸展策略为 Expanding
    ui->tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    QStringList diseases;
    diseases << "非酒精性脂肪肝EC"<< "非酒精性脂肪肝IC"<< "非酒精脂肪肝炎EC"<< "非酒精脂肪肝炎IC"<< "肝硬化IC"<< "肝硬化EC";
    ui->diseaseBox->addItems(diseases);
    connect(ui->diseaseBox,&QComboBox::currentTextChanged,this,&DataTableViewer::onDiseaseBoxChanged);

    QPluginLoader pluginLoader("D:\\Projects\\QTProjects\\QT_Ueyes\\build-QT_Ueyes-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\modules\\SqlLite_Lib\\libSqlLite_Lib.dll");
    QObject *plugin = pluginLoader.instance();
    ui->tableView->setSortingEnabled(true);  //启动排序

    m_pInterface = qobject_cast<DeclareInterface *>(plugin);
    QString db_name  = "C:\\Users\\HarryWen\\Desktop\\test.db";
    data_model = connectDB(db_name,cur_table_name);
    ui->tableView->setModel(data_model);

    connect(ui->searchBox,&QPlainTextEdit::textChanged,this,&DataTableViewer::on_textEdit_textChanged);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect( ui->tableView,     SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tableContextMenuRequested(QPoint)));
    connect( ui->saveButton, &QPushButton::clicked, this, &DataTableViewer::on_pushButton_3_clicked);
    connect( ui->revertButton,&QPushButton::clicked, this, &DataTableViewer::on_pushButton_4_clicked);
    initWidget2();
}

void DataTableViewer::initWidget2()
{
    ui->tableView_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList table_h_headers;
    for(int i=0;i<data_model->columnCount();i++)
        table_h_headers<<data_model->headerData(i,Qt::Horizontal).toString();

    db_table_model_->setHorizontalHeaderLabels(table_h_headers);
    ui->tableView_2->setModel(model2);
}
QSqlTableModel* DataTableViewer::connectDB(QString db_name,QString table_name)
{
    QSqlDatabase db = m_pInterface->connectDB(db_name);
    QSqlTableModel* model = m_pInterface->queryEntireTable(table_name);
    model2 = m_pInterface->queryEntireTable2("非酒精性脂肪肝IC");

    return model;
}

QWidget* DataTableViewer::createDataVisualTable(int page)
{
//    switchPage(page);
    return new QWidget();
}

void DataTableViewer::onDiseaseBoxChanged(const QString &text) {
    qDebug() << "Selected or entered text:" << text;
    QString table_name = text;
    if (cur_table_name != table_name)
    {
        cur_table_name = table_name;
        data_model =  m_pInterface->queryEntireTable(cur_table_name);
    }
}



void DataTableViewer::on_textEdit_textChanged()
{
    QStringList columns;
    columns<<"class";
    QString text = ui->searchBox->toPlainText();
    m_pInterface->searchTableItem(columns,text);

}
void DataTableViewer::tableContextMenuRequested(const QPoint &pos)
{
    int x = pos.x ();
    int y = pos.y ();
    QModelIndex index = ui->tableView->indexAt (QPoint(x,y));
    int row  = index.row ();//获得QTableWidget列表点击的行数

    QMenu menu;
    QAction *add_row_up = menu.addAction(tr("向上增加一行"));
    QAction *add_row_down = menu.addAction(tr("向下增加一行"));
    QAction *delete_row = menu.addAction(tr("删除行"));
    QAction *monitor_row = menu.addAction(tr("添加到监视"));


    connect(add_row_up, &QAction::triggered, [=](){
        data_model->insertRow(row); //添加一行
    });
    connect(add_row_down, &QAction::triggered, [=](){
        data_model->insertRow(row+1); //添加一行
    });
    connect(delete_row, &QAction::triggered, [=](){
        data_model->removeRow(row);
    });
    connect(monitor_row, &QAction::triggered, [=](){
        model2->insertRow(0);

        for (int i =0;i<data_model->columnCount();i++)
        {
            QString name = data_model->data(data_model->index(row,i)).toString();
            model2->setData(model2->index(0,i),name);
        }




    });
    menu.show ();
    menu.exec(QCursor::pos());
}

void DataTableViewer::on_pushButton_3_clicked()
{
    data_model->database().transaction(); //开始事务操作
    if (data_model->submitAll()) {
        qDebug() << "Selected or entered text:";

        data_model->database().commit(); //提交
    } else {
        data_model->database().rollback(); //回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                             .arg(data_model->lastError().text()));
    }
}
void DataTableViewer::on_pushButton_4_clicked()
{
    qDebug() << "Selected or entered text:";
    data_model->database().rollback(); //回滚

    data_model->revertAll();
}

