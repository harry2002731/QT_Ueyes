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
 #include "pythonlib.h"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

DataTableViewer::DataTableViewer() : ui(new Ui::DataTableViewer1)
{
    ui->setupUi(this);
    int cur_Page = 0;                            // 当前页数
    int num_each_page = 10;                      // 每页数据个数
    int total_pages = 10;                        // 总共的数据页数
    QString cur_table_name = "非酒精性脂肪肝EC"; // 当前查询表的名字
    QString search_item = "";
    this->initWidget();

    //    FuncViewerWidget();
    //    PythonLib* py = new PythonLib();
    //    PythonLib* py = new PythonLib();

    //    auto aaa = py->callMethod("svm_test","SvmAnalyzer","predict","每日酗酒");
    //    QVector<QPair<QVariant, QVariant>> array2D;
    //    py->parsePyObject(aaa,array2D);
}

void DataTableViewer::initWidget()
{

    initTableViewLeftMain();
    QPluginLoader pluginLoader("D:\\Projects\\QTProjects\\QT_Ueyes\\build-QT_Ueyes-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\x64\\bin\\libSqlLite_Lib.dll");
    QObject *plugin = pluginLoader.instance();
    m_pInterface = qobject_cast<DeclareInterface *>(plugin);
    QString db_name = "C:\\Users\\HarryWen\\Desktop\\test.db";
    data_model = connectDB(db_name, "纳排疾病数据");

    standardModel = new QStandardItemModel(data_model->rowCount(), data_model->columnCount() + 1, this);
    ui->tableViewLeft->setModel(standardModel);
    ui->tableViewLeft->setContextMenuPolicy(Qt::CustomContextMenu);

    buttonGroup->setExclusive(false);

    updateModel();
    initSlots();

    initTableViewRight();
    initTableViewRightBottom();
    //    initChart();
    //    this->setStyleSheet("QTableView::item:first { border-top: 2px solid black; }");
    //    ui->label->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    //    ui->label_3->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    //    this->setStyleSheet("background-color: white;");
    //        this->setStyleSheet(QString::fromUtf8("#tableView{border:3px solid black}"));
}

void DataTableViewer::initTableViewLeftMain()
{
    ui->tableViewLeft->setSortingEnabled(true);                                    // 启动排序
    ui->tableViewLeft->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // 滑动条设置
    ui->tableViewLeft->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel); // 滑动条设置
    QHeaderView *headerView = ui->tableViewLeft->horizontalHeader();
    headerView->setFont(QFont("Arial", 10, QFont::Bold));
    ui->tableViewLeft->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(220,220,220);color: black;}");
    ui->tableViewLeft->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(220,220,220);color: black;}");
    ui->tableViewLeft->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);

    QHeaderView *header = ui->tableViewLeft->horizontalHeader();
    for (int i = 0; i < header->count(); ++i)
    {
        header->setSectionResizeMode(i, QHeaderView::Interactive);
    }

    QStringList diseases;
    diseases << "非酒精性脂肪肝" << "非酒精脂肪肝炎" << "肝硬化";
    ui->diseaseBox->addItems(diseases);

    QStringList analyzes;
    analyzes << "原始数据" << "降重数据";
        ui->analyzeBox->addItems(analyzes);

    QStringList icec;
    icec << "EC" << "IC";
    ui->ecicBox->addItems(icec);
    connect(ui->tableViewLeft, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tableContextMenuRequested(QPoint)));
}

void DataTableViewer::initTableViewRight()
{
    ui->tableViewRight->setSortingEnabled(true); // 启动排序
    ui->tableViewRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tableViewRight->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *headerView = ui->tableViewLeft->horizontalHeader();
    headerView->setFont(QFont("Arial", 10, QFont::Bold));
    ui->tableViewRight->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(220,220,220);color: black;}");
    ui->tableViewRight->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(220,220,220);color: black;}");
    ui->tableViewRight->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);

    QStringList table_h_headers;
    for (int i = 0; i < data_model->columnCount(); i++)
        table_h_headers << data_model->headerData(i, Qt::Horizontal).toString();

    standardModelRightTop = new QStandardItemModel(0, data_model->columnCount(), this);
    standardModelRightTop->setHorizontalHeaderLabels(table_h_headers);

    ui->tableViewRight->setModel(standardModelRightTop);
    ui->tableViewRight->setColumnHidden(5, true);
    ui->tableViewRight->setColumnHidden(7, true);
    ui->tableViewRight->setColumnHidden(8, true);
    ui->tableViewRight->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableViewRight, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tableRightContextMenuRequested(QPoint)));
}
void DataTableViewer::initTableViewRightBottom()
{
    //    ui->tableViewRightBottom->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //    ui->tableViewRightBottom->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //    QStringList table_h_headers;
    //    for (int i = 0; i < data_model->columnCount(); i++)
    //        table_h_headers << data_model->headerData(i, Qt::Horizontal).toString();

    //    standardModelRightBottom = new QStandardItemModel(0, data_model->columnCount(), this);
    //    standardModelRightBottom->setHorizontalHeaderLabels(table_h_headers);

    //    ui->tableViewRightBottom->setModel(standardModelRightBottom);
    //    ui->tableViewRightBottom->setColumnHidden(8, true);
    //    ui->tableViewRightBottom->setColumnHidden(9, true);
}

void DataTableViewer::initSlots()
{
    connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(on_buttonGroup_Pressed(int)));

    connect(ui->addButton, &QPushButton::clicked, this, &DataTableViewer::on_topButton_clicked);
    //    connect(ui->pushButtonRighrtBottom, &QPushButton::clicked, this, &DataTableViewer::on_bottomButton_clicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &DataTableViewer::on_saveButton_clicked);
    connect(ui->revertButton, &QPushButton::clicked, this, &DataTableViewer::on_revertButton_clicked);
    connect(ui->analyzeBox, &QComboBox::currentTextChanged, this, &DataTableViewer::on_analyzeBox_changed);
    connect(ui->ecicBox, &QComboBox::currentTextChanged, this, &DataTableViewer::on_ecic_clicked);

    //    connect(ui->exportButton, &QPushButton::clicked, this, &DataTableViewer::on_exportButton_clicked);
    connect(ui->diseaseBox, &QComboBox::currentTextChanged, this, &DataTableViewer::on_diseaseBox_changed);
    connect(ui->searchBox, &QPlainTextEdit::textChanged, this, &DataTableViewer::on_textEdit_textChanged);
}

void DataTableViewer::on_exportButton_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, tr("文件选取"), "C:", tr("xlsx文件(*xlsx)"));
    if (file_path != "")
        exportXlsx(*standardModelRightTop, file_path);
}

void DataTableViewer::exportXlsx(QStandardItemModel &model, QString file_path)
{

    QXlsx::Document xlsxW;
    int row_count = model.rowCount();
    int column_count = model.columnCount();

    QXlsx::Format header;
    header.setFontBold(true);

    QStringList table_h_headers;
    for (int i = 0; i < data_model->columnCount(); i++)
    {
        xlsxW.write(1, i + 1, data_model->headerData(i, Qt::Horizontal), header); // write "Hello Qt!" to cell(A,1).
    }

    for (int row = 0; row < row_count; row++)
    {
        for (int column = 0; column < column_count; column++)
        {
            QStandardItem *item = model.item(row, column);
            if (item)
            {
                QVariant variantData = item->data(Qt::DisplayRole);
                xlsxW.write(row + 2, column + 1, variantData); // write "Hello Qt!" to cell(A,1).
            }
        }
    }
    xlsxW.saveAs(file_path); // save the document as 'Test.xlsx'
}
void DataTableViewer::updateModel()
{
    QStringList table_h_headers;
    table_h_headers << "";
    for (int i = 0; i < data_model->columnCount(); i++)
        table_h_headers << data_model->headerData(i, Qt::Horizontal).toString();
    standardModel->setHorizontalHeaderLabels(table_h_headers);

    for (int row = 0; row < data_model->rowCount(); ++row)
    {
        for (int column = 0; column < data_model->columnCount(); ++column)
        {
            QStandardItem *item = new QStandardItem(data_model->data(data_model->index(row, column), Qt::DisplayRole).toString());
            item->setTextAlignment(Qt::AlignCenter);
            standardModel->setItem(row, column + 1, item);
            QCheckBox *button = new QCheckBox();
            buttonGroup->addButton(button, row);
            ui->tableViewLeft->setIndexWidget(standardModel->index(row, 0), button);
        }
    };

    //    ui->tableView->setColumnHidden(2, true);
    ui->tableViewLeft->setColumnHidden(6, true);
    ui->tableViewLeft->setColumnHidden(8, true);
//    ui->tableViewLeft->setColumnHidden(9, true);

    ui->tableViewLeft->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    // 列宽度显示限制
    int maxWidth = 200;
    QHeaderView *header = ui->tableViewLeft->horizontalHeader();
    for (int i = 0; i < standardModel->columnCount(); ++i)
    {
        // 获取列的建议宽度
        int hintWidth = header->sectionSize(i);
        if (hintWidth > maxWidth)
        {
            ui->tableViewLeft->setColumnWidth(i, maxWidth);
        }
        else
        {
            ui->tableViewLeft->setColumnWidth(i, hintWidth);
        }
    }
}

QSqlTableModel *DataTableViewer::connectDB(QString db_name, QString table_name)
{
    QSqlDatabase db = m_pInterface->connectDB(db_name);
    QSqlTableModel *model = m_pInterface->queryEntireTable(table_name);
    return model;
}

void DataTableViewer::initChart()
{
    // 饼状图
    pie_series = new QPieSeries(this);
    connect(pie_series, SIGNAL(clicked(QPieSlice *)), this, SLOT(onPieSeriesClicked(QPieSlice *)));

    // 定义各扇形切片的颜色
    static const QStringList list_pie_color = {
        "#6480D6",
        "#A1DC85",
        "#FFAD25",
        "#FF7777",
        "#84D1EF",
        "#4CB383",
    };

    // 设置数据
    QList<qreal> list_data = {3.1, 3.2, 3.3, 3.4, 3.5, 3.6};

    // 扇形
    for (int i = 0; i < list_pie_color.size(); i++)
    {
        QPieSlice *pie_slice = new QPieSlice(this);
        pie_slice->setLabelVisible(true);
        pie_slice->setValue(list_data[i]);
        pie_slice->setLabel(QString::number(list_data[i]));
        pie_slice->setColor(list_pie_color[i]);
        pie_slice->setLabelColor(list_pie_color[i]);
        pie_slice->setBorderColor(list_pie_color[i]);
        pie_series->append(pie_slice);
    }

    // 图表视图
    QChart *chart = new QChart;
    chart->setTitle("纳排分类饼图");
    chart->setTheme(QChart::ChartThemeQt);

    // 标题字体
    QFont font = qApp->font();
    font.setBold(true);
    font.setPointSize(16);
    chart->setTitleFont(font);

    // 加入饼图
    chart->addSeries(pie_series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 图例
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setBackgroundVisible(false);

    // 加入绘画视图
    QChartView *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

    // 加入布局
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);
    //    ui->widget->setLayout(layout);
}

// 点击饼图
void DataTableViewer::onPieSeriesClicked(QPieSlice *slice)
{
    slice->setExploded(!slice->isExploded());
}
// 切换查询
void DataTableViewer::on_diseaseBox_changed(const QString &text)
{
    QString disease_name = text;
    if (cur_disease_name != disease_name)
    {
        cur_disease_name = disease_name;
        test();
    }
}

// 数据分析
void DataTableViewer::on_analyzeBox_changed(const QString &text)
{
    if (cur_analyze_state != text)
    {
        cur_analyze_state = text;
        test();
    }
}

void DataTableViewer::on_ecic_clicked(const QString &text)
{
    if (cur_icec_state != text)
    {
        cur_icec_state = text;
        test();
    }
    //    QStringList columns;
    //    columns << "纳排分类";
    //    m_pInterface->searchTableItem(columns, cur_icec_state);
    //    updateModel();
}

void DataTableViewer::test()
{
    QStringList columns1;
    columns1 << "疾病名称";
    m_pInterface->searchTableItem(columns1, cur_disease_name);

    QStringList columns2;
    columns2 << "类别内相似度值";
    if (cur_analyze_state == "降重数据")
        m_pInterface->searchNonZeroItem(columns2, cur_analyze_state);

    QStringList columns3;
    columns3 << "纳排分类";
    m_pInterface->searchTableItem(columns3, cur_icec_state);

    QStringList columns4;
    columns4 << "类别";
    m_pInterface->searchTableItem(columns4, cur_search_txt);
    m_pInterface->searchNow();
    updateModel();
}
void DataTableViewer::on_topButton_clicked()
{

    for (auto item : select_set)
    {
        standardModelRightTop->insertRow(0);

        for (int i = 0; i < data_model->columnCount(); i++)
        {
            QString name = data_model->data(data_model->index(item, i)).toString();

            standardModelRightTop->setData(standardModelRightTop->index(0, i), name);
        }
    }
    select_set.clear();

}
void DataTableViewer::on_bottomButton_clicked()
{
//    for (auto item : select_set)
//    {
//        standardModelRightBottom->insertRow(0);

//        for (int i = 0; i < data_model->columnCount(); i++)
//        {
//            QString name = data_model->data(data_model->index(item, i)).toString();

//            standardModelRightBottom->setData(standardModelRightBottom->index(0, i), name);
//        }
//    }
//    select_set.clear();
    //    QStringList columns;
    //    columns<<"class";
    //    QString text = ui->searchBox->toPlainText();
    //    m_pInterface->searchTableItem(columns,text);
}
void DataTableViewer::on_buttonGroup_Pressed(int id)
{
    qDebug() << "Button" << id << "pressed";
    select_set.insert(id);
}
void DataTableViewer::on_textEdit_textChanged()
{
    cur_search_txt = ui->searchBox->toPlainText();
    test();
}

void DataTableViewer::tableContextMenuRequested(const QPoint &pos)
{
    int x = pos.x();
    int y = pos.y();
    QModelIndex index = ui->tableViewLeft->indexAt(QPoint(x, y));
    int row = index.row(); // 获得QTableWidget列表点击的行数
    int column = index.column();

    QMenu menu;
    QAction *add_row_up = menu.addAction(tr("向上增加一行"));
    QAction *add_row_down = menu.addAction(tr("向下增加一行"));
    QAction *delete_row = menu.addAction(tr("删除行"));
    QAction *classfier = menu.addAction(tr("数据分类"));

    connect(add_row_up, &QAction::triggered, [=]()
            {
                data_model->insertRow(row); //添加一行
                updateModel(); });
    connect(add_row_down, &QAction::triggered, [=]()
            {
                data_model->insertRow(row+1); //添加一行
                updateModel(); });
    connect(delete_row, &QAction::triggered, [=]()
            {
                data_model->removeRow(row);
                updateModel(); });
    connect(classfier, &QAction::triggered, [=]()
            {
                QModelIndex index = data_model->index(row, column+1); // 假设第一列是id列

                QVariant value = data_model->data(index, Qt::DisplayRole);
                QString str = value.value<QString>();

                py = new PythonLib();
                auto predict = py->callMethod("svm_test", "SvmAnalyzer", "predict", str);
                QVector<QPair<QVariant, QVariant>> array2D;
                py->parsePyObject(predict, array2D);
                data_model->setData(index, array2D.at(0).first.value<QString>());
                updateModel();
            });

    menu.show();
    menu.exec(QCursor::pos());
}

void DataTableViewer::tableRightContextMenuRequested(const QPoint &pos)
{
    int x = pos.x();
    int y = pos.y();

    QModelIndex index = ui->tableViewRight->indexAt(QPoint(x, y));
    int row = index.row(); // 获得QTableWidget列表点击的行数
    int column = index.column();

    QMenu menu;
    QAction *add_row_up = menu.addAction(tr("向上增加一行"));
    QAction *add_row_down = menu.addAction(tr("向下增加一行"));
    QAction *delete_row = menu.addAction(tr("删除行"));

    connect(add_row_up, &QAction::triggered, [=]()
            {
                standardModelRightTop->insertRow(row); // 添加一行
            });
    connect(add_row_down, &QAction::triggered, [=]()
            {
                standardModelRightTop->insertRow(row + 1); // 添加一行
            });
    connect(delete_row, &QAction::triggered, [=]()
            { standardModelRightTop->removeRow(row); });

    menu.show();
    menu.exec(QCursor::pos());
}
void DataTableViewer::on_saveButton_clicked()
{
    data_model->database().transaction(); // 开始事务操作
    if (data_model->submitAll())
    {
        data_model->database().commit(); // 提交
    }
    else
    {
        data_model->database().rollback(); // 回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1")
                                 .arg(data_model->lastError().text()));
    }
}
void DataTableViewer::on_revertButton_clicked()
{
    qDebug() << "Selected or entered text:";
    data_model->database().rollback(); // 回滚

    data_model->revertAll();
}
