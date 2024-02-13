#include "FuncViewerWidget.h"
#include "qpushbutton.h"
#include "ui_FuncViewerWidget.h"
#include "FuncViewerPage.h"
#include "Form.h"

FuncViewerWidget::FuncViewerWidget() :
    QWidget(),
    ui(new Ui::FuncViewerWidget)
{
    ui->setupUi(this);
    QWidget *widget = new QWidget(this);
    m_pContentVBoxLayout = new QVBoxLayout();
    m_pContentVBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_pContentVBoxLayout->setSpacing(2);//设置上下间距
//    m_pContentVBoxLayout->addStretch(1);

    QVBoxLayout *vBoxLayout = new QVBoxLayout(widget);
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->addLayout(m_pContentVBoxLayout);
    vBoxLayout->addStretch(1);
    ui->scrollArea->setWidget(widget);


    this->addWidget(QStringLiteral("Qt小罗"), new Form());
    this->addWidget(QStringLiteral("Qt小罗"), new Form());

    this->addWidget(QStringLiteral("Qt小罗"), new Form());
                                              this->addWidget(QStringLiteral("Qt小罗"), new Form());
                                              this->addWidget(QStringLiteral("Qt小罗"), new Form());
                                                                                        this->addWidget(QStringLiteral("Qt小罗"), new Form());
                                                                                        this->addWidget(QStringLiteral("Qt小罗"), new Form());

    this->addWidget(QStringLiteral("Qt小罗111"), new QWidget());

}


FuncViewerWidget::~FuncViewerWidget()
{
    delete ui;
}

void FuncViewerWidget::addWidget(QString title, QWidget *widget)
{
    FuncViewerPage *page = new FuncViewerPage(this);
    page->addWidget(title, widget);

    m_pContentVBoxLayout->addWidget(page);
}

