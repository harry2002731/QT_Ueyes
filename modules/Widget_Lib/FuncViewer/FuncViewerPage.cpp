#include "FuncViewerPage.h"
#include "ui_FuncViewerPage.h"


FuncViewerPage::FuncViewerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FuncViewerPage),
    m_bIsExpanded(true),
    m_pLabel(nullptr)
{
    ui->setupUi(this);

    ui->widgetContent->setAttribute(Qt::WA_StyledBackground);

    m_pLabel = new QLabel(this);
    m_pLabel->setFixedSize(20, 20);
    m_pLabel->setPixmap(QPixmap(":/img/down-arrow.png").scaled(m_pLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    QHBoxLayout *layout = new QHBoxLayout(ui->pushButtonFold);
    layout->setContentsMargins(0, 0, 5, 0);
    layout->addStretch(1);
    layout->addWidget(m_pLabel);

    QFile file(":/qss/toolpage.qss");
    if (file.open(QIODevice::ReadOnly)) {
        setStyleSheet(file.readAll());
    }
    file.close();

    connect(ui->pushButtonFold, &QPushButton::clicked, this, &FuncViewerPage::onPushButtonFoldClicked);
}

//FuncViewerPage::~FuncViewerPage()
//{
//    delete ui;
//}

void FuncViewerPage::addWidget(const QString &title, QWidget *widget)
{
    ui->pushButtonFold->setText(title);
    ui->verticalLayoutContent->addWidget(widget);
}

void FuncViewerPage::expand()
{
    ui->widgetContent->show();
    m_bIsExpanded = true;

    m_pLabel->setPixmap(QPixmap(":/img/down-arrow.png").scaled(m_pLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void FuncViewerPage::collapse()
{
    ui->widgetContent->hide();
    m_bIsExpanded = false;

    m_pLabel->setPixmap(QPixmap(":/img/left-arrow.png").scaled(m_pLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void FuncViewerPage::onPushButtonFoldClicked()
{
    if (m_bIsExpanded) {
        collapse();
    } else {
        expand();
    }
}
