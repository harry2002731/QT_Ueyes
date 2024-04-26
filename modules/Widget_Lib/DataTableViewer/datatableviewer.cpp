#include "datatableviewer.h"
#include "qcheckbox.h"
#include "qidentityproxymodel.h"
#include "qmenu.h"
#include "qsqlerror.h"
#include "qsqlquerymodel.h"
#include "qstandarditemmodel.h"
#include "ui_DataTableViewer.h"
#include <QMessageBox>
#include <QButtonGroup>

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
//    ui->tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *header = ui->tableView->horizontalHeader();
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

    standardModel = new QStandardItemModel(data_model->rowCount(), data_model->columnCount()+1, this);
    ui->tableView->setModel(standardModel);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    updateModel();
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(onButtonPressed(int)));


//    // 设置第一列的大小调整方式（例如，固定大小或根据内容调整大小）
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    // 遍历剩余的列，设置它们为自动伸展
    for (int i = 1; i < header->count(); ++i) {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui->tableView->resizeColumnsToContents();
    connect(ui->pushButton,&QPushButton::clicked,this,&DataTableViewer::on_top_Button_clicked);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&DataTableViewer::on_bottom_Button_clicked);

    connect(ui->searchBox,&QPlainTextEdit::textChanged,this,&DataTableViewer::on_textEdit_textChanged);

    connect( ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tableContextMenuRequested(QPoint)));
    connect( ui->saveButton, &QPushButton::clicked, this, &DataTableViewer::on_pushButton_3_clicked);
    connect( ui->revertButton,&QPushButton::clicked, this, &DataTableViewer::on_pushButton_4_clicked);
    initTableViewRightTop();
    initTableViewRightBottom();
//    initChart();
    ui->label->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    ui->label_3->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");

    ui->label_4->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");

}
void DataTableViewer::updateModel()
{
    for (int row = 0; row < data_model->rowCount(); ++row)   {
        for (int column = 0; column < data_model->columnCount(); ++column) {
            // 创建QStandardItem并设置文本
            QStandardItem *item = new QStandardItem(data_model->data(data_model->index(row, column), Qt::DisplayRole).toString());
            standardModel->setItem(row, column+1, item);

            QCheckBox * button = new QCheckBox();
            buttonGroup->addButton(button, row);

            ui->tableView->setIndexWidget(standardModel->index(row, 0), button);
        }
    };


}
void DataTableViewer::initTableViewRightTop()
{
    ui->tableViewRightTop->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableViewRightTop->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList table_h_headers;
    for(int i=0;i<data_model->columnCount();i++)
        table_h_headers<<data_model->headerData(i,Qt::Horizontal).toString();

    standardModelRightTop = new QStandardItemModel(0, data_model->columnCount(), this);
    standardModelRightTop->setHorizontalHeaderLabels(table_h_headers);

    ui->tableViewRightTop->setModel(standardModelRightTop);
}
void DataTableViewer::initTableViewRightBottom()
{
    ui->tableViewRightBottom->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableViewRightBottom->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList table_h_headers;
    for(int i=0;i<data_model->columnCount();i++)
        table_h_headers<<data_model->headerData(i,Qt::Horizontal).toString();

    standardModelRightBottom = new QStandardItemModel(0, data_model->columnCount(), this);
    standardModelRightBottom->setHorizontalHeaderLabels(table_h_headers);

    ui->tableViewRightBottom->setModel(standardModelRightBottom);
}
QSqlTableModel* DataTableViewer::connectDB(QString db_name,QString table_name)
{
    QSqlDatabase db = m_pInterface->connectDB(db_name);
    QSqlTableModel* model = m_pInterface->queryEntireTable(table_name);
    return model;
}

QWidget* DataTableViewer::createDataVisualTable(int page)
{
//    switchPage(page);
    return new QWidget();
}



void DataTableViewer::initChart()
{
    //饼状图
    pie_series = new QPieSeries(this);
    connect(pie_series, SIGNAL(clicked(QPieSlice*)), this, SLOT(onPieSeriesClicked(QPieSlice*)));

    //定义各扇形切片的颜色
    static const QStringList list_pie_color = {
        "#6480D6","#A1DC85","#FFAD25","#FF7777","#84D1EF","#4CB383",
    };

    //设置数据
    QList<qreal> list_data = {3.1, 3.2, 3.3, 3.4, 3.5, 3.6};

    //扇形
    for (int i = 0; i < list_pie_color.size(); i++) {
        QPieSlice* pie_slice = new QPieSlice(this);
        pie_slice->setLabelVisible(true);
        pie_slice->setValue(list_data[i]);
        pie_slice->setLabel(QString::number(list_data[i]));
        pie_slice->setColor(list_pie_color[i]);
        pie_slice->setLabelColor(list_pie_color[i]);
        pie_slice->setBorderColor(list_pie_color[i]);
        pie_series->append(pie_slice);
    }

    //图表视图
    QChart* chart = new QChart;
    chart->setTitle("纳排分类饼图");
    chart->setTheme(QChart::ChartThemeQt);

    //标题字体
    QFont font = qApp->font();
    font.setBold(true);
    font.setPointSize(16);
    chart->setTitleFont(font);

    //加入饼图
    chart->addSeries(pie_series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    //图例
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setBackgroundVisible(false);

    //加入绘画视图
    QChartView* chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

    //加入布局
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);
//    ui->widget->setLayout(layout);
}

//点击饼图
void DataTableViewer::onPieSeriesClicked(QPieSlice* slice)
{
    slice->setExploded(!slice->isExploded());
}
void DataTableViewer::onDiseaseBoxChanged(const QString &text) {
    qDebug() << "Selected or entered text:" << text;
    QString table_name = text;
    if (cur_table_name != table_name)
    {
        cur_table_name = table_name;
        data_model =  m_pInterface->queryEntireTable(cur_table_name);
    }
    updateModel();

}


void DataTableViewer::on_top_Button_clicked()
{

    for (auto item:select_set){
        standardModelRightTop->insertRow(0);

        for (int i =0;i<data_model->columnCount();i++)
        {
            QString name = data_model->data(data_model->index(item,i)).toString();

            standardModelRightTop->setData(standardModelRightTop->index(0,i),name);
        }
    }
    select_set.clear();
}
void DataTableViewer::on_bottom_Button_clicked()
{
    for (auto item:select_set){
        standardModelRightBottom->insertRow(0);

        for (int i =0;i<data_model->columnCount();i++)
        {
            QString name = data_model->data(data_model->index(item,i)).toString();

            standardModelRightBottom->setData(standardModelRightBottom->index(0,i),name);
        }
    }
    select_set.clear();
//    QStringList columns;
//    columns<<"class";
//    QString text = ui->searchBox->toPlainText();
//    m_pInterface->searchTableItem(columns,text);
}
void DataTableViewer::onButtonPressed(int id) {

    qDebug() << "Button" << id << "pressed";
    select_set.insert(id);
}
void DataTableViewer::on_textEdit_textChanged()
{
    QStringList columns;
    columns<<"class";
    QString text = ui->searchBox->toPlainText();
    m_pInterface->searchTableItem(columns,text);
    updateModel();

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
//    QAction *monitor_row = menu.addAction(tr("添加到监视"));


    connect(add_row_up, &QAction::triggered, [=](){
        data_model->insertRow(row); //添加一行
        updateModel();

    });
    connect(add_row_down, &QAction::triggered, [=](){
        data_model->insertRow(row+1); //添加一行
        updateModel();

    });
    connect(delete_row, &QAction::triggered, [=](){
        data_model->removeRow(row);
        updateModel();

    });
//    connect(monitor_row, &QAction::triggered, [=](){
//        model2->insertRow(0);

//        for (int i =0;i<data_model->columnCount();i++)
//        {
//            QString name = data_model->data(data_model->index(row,i)).toString();
//            model2->setData(model2->index(0,i),name);
//        }
//    });
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

