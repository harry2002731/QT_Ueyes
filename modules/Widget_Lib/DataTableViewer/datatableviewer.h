#ifndef DATATABLEVIEWER_H
#define DATATABLEVIEWER_H
#include <QtCharts/QtCharts>

#include "DataTableViewer_global.h"
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
    void initChart();
    void initSlots();
    void initWidget();
    void initTableViewLeftMain();
    void initTableViewRightTop();
    void initTableViewRightBottom();


    QSqlTableModel* connectDB(QString db_name,QString table_name);
    void updateModel();
    QString cur_table_name = "非酒精性脂肪肝EC"; //当前查询表的名字
    DeclareInterface* m_pInterface = nullptr;  //获取插件类型
    Ui::DataTableViewer1 *ui;
    QSqlTableModel* data_model;
    QSqlTableModel* model2;
    QStandardItemModel* db_table_model_  = new QStandardItemModel();
    QSet<int> select_set;
    QStandardItemModel *standardModelRightBottom;
    QStandardItemModel *standardModelRightTop;
    QPieSeries *pie_series;
    QButtonGroup *buttonGroup = new QButtonGroup();
    QStandardItemModel *standardModel ;
public slots:
    void tableContextMenuRequested(const QPoint &pos);
    void on_buttonGroup_Pressed(int id) ;

    void on_topButton_clicked();
    void on_bottomButton_clicked();

    void on_saveButton_clicked();
    void on_revertButton_clicked();
    void on_analyzeButton_clicked();

    void on_diseaseBox_changed(const QString &text);
    void on_textEdit_textChanged();

    void onPieSeriesClicked(QPieSlice* slice);


};

#endif // DATATABLEVIEWER_H
