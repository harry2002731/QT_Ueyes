#ifndef DATATABLEVIEWER_H
#define DATATABLEVIEWER_H

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
    QWidget* createDataVisualTable(int page);
    void initWidget();
    void initWidget2();

    QSqlTableModel* connectDB(QString db_name,QString table_name);
    void onDiseaseBoxChanged(const QString &text);
    void initChart();
    QString cur_table_name = "非酒精性脂肪肝EC"; //当前查询表的名字
    DeclareInterface* m_pInterface = nullptr;  //获取插件类型
    Ui::DataTableViewer1 *ui;
    QSqlTableModel* data_model;
    QSqlTableModel* model2;
    QStandardItemModel* db_table_model_  = new QStandardItemModel();

public slots:
    void on_textEdit_textChanged();
    void tableContextMenuRequested(const QPoint &pos);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();


};

#endif // DATATABLEVIEWER_H
