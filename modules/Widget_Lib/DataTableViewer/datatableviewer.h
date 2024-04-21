#ifndef DATATABLEVIEWER_H
#define DATATABLEVIEWER_H

#include "DataTableViewer_global.h"
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
    QSqlQueryModel* connectDB(QString db_name,QString table_name);
    void onDiseaseBoxChanged(const QString &text);

    QString cur_table_name = "非酒精性脂肪肝EC"; //当前查询表的名字
    DeclareInterface* m_pInterface = nullptr;  //获取插件类型
    Ui::DataTableViewer1 *ui;
    QSqlQueryModel* data_model;


public slots:
    void on_textEdit_textChanged();
};

#endif // DATATABLEVIEWER_H
