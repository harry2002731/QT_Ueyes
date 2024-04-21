#include "datatableviewer.h"
//#include "qboxlayout.h"
//#include "qcombobox.h"
//#include "qheaderview.h"
//#include "qlineedit.h"
//#include "qpushbutton.h"
#include "qlineedit.h"
#include "qsqlquerymodel.h"
#include "ui_DataTableViewer.h"

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
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


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


}
QSqlQueryModel* DataTableViewer::connectDB(QString db_name,QString table_name)
{
    QSqlDatabase db = m_pInterface->connectDB(db_name);
    QSqlQueryModel* model = m_pInterface->queryEntireTable(table_name);
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
