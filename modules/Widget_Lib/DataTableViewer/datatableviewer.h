
#ifndef DATATABLEVIEWER_H
#define DATATABLEVIEWER_H
#include <QtCharts/QtCharts>


#include "DataTableViewer_global.h"
#include "pythonlib.h"
#include "qstandarditemmodel.h"
#include "qwidget.h"
#include <QPluginLoader>
#include "SqlInterface.h"
#include "qsqltablemodel.h"

namespace Ui {
class DataTableViewer1;
}

class DATATABLEVIEWER_EXPORT DataTableViewer : public QWidget
{
    Q_OBJECT
public:
    DataTableViewer();

    QString cur_disease_name = "非酒精性脂肪肝"; //当前查询的疾病
    QString cur_icec_state = "EC"; //当前查询的icec状态
    QString cur_analyze_state = "原始数据"; //当前查询的icec状态
    QString cur_search_txt = "";

    void initChart();
    void initSlots();
    void initWidget();
    void initTableViewLeftMain();
    void initTableViewRight();

    QSqlTableModel* connectDB(QString db_name,QString table_name);
    void exportXlsx(QStandardItemModel &model, QString file_path);
    void updateModel();
    void test();


    DeclareInterface* m_pInterface = nullptr;  //获取插件类型
    Ui::DataTableViewer1 *ui;
    QSqlTableModel* data_model;
    PythonLib* py = new PythonLib();
    QSet<int> select_set;
    QPieSeries *pie_series;

    QButtonGroup *buttonGroup = new QButtonGroup();
    QStandardItemModel* db_table_model_  = new QStandardItemModel();
    QStandardItemModel* standardModelRightTop;
    QStandardItemModel* standardModel ;


public slots:
    void tableContextMenuRequested(const QPoint &pos);
    void tableRightContextMenuRequested(const QPoint &pos);

    void on_cleanButton_clicked();
    void on_buttonGroup_Pressed(int id) ;

    void on_topButton_clicked();

    void on_saveButton_clicked();
    void on_revertButton_clicked();
    void on_exportButton_clicked();
    void on_reloadButton_clicked();

    void on_analyzeBox_changed(const QString &text);
    void on_diseaseBox_changed(const QString &text);
    void on_icecBox_clicked(const QString &text);

    void on_searchEditor_textChanged();

    void onPieSeriesClicked(QPieSlice* slice);


};

#endif // DATATABLEVIEWER_H
