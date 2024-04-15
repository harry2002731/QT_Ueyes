#ifndef FUNCVIEWERPAGE_H
#define FUNCVIEWERPAGE_H

#include "qlabel.h"
#include <QObject>
#include <QWidget>
#include "qpushbutton.h"
#include <QDebug>
#include <QFormLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>


namespace Ui {
class FuncViewerPage;
}


class FuncViewerPage: public QWidget
{
    Q_OBJECT
public:
    FuncViewerPage(QWidget *parent);
    QWidget * widgetContent;
    QPushButton *pushButtonFold;
    QVBoxLayout *verticalLayoutContent;
    Ui::FuncViewerPage *ui;

public slots:
    void addWidget(const QString &title, QWidget *widget);
    void expand();
    void collapse();

private slots:
    void onPushButtonFoldClicked();

private:

    bool m_bIsExpanded;
    QLabel *m_pLabel;

};

#endif // FUNCVIEWERPAGE_H
