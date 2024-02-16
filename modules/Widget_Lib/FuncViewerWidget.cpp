#include "FuncViewerWidget.h"
#include "ui_FuncViewerWidget.h"
#include "FuncViewerPage.h"
#include "Form.h"


FuncViewerWidget::FuncViewerWidget() :
    QWidget()
{

    this->initWidget();


    this->addWidget(QStringLiteral("Qt小罗"), new Form());
//    this->addWidget(QStringLiteral("Qt小罗"), new Form());
//    this->addWidget(QStringLiteral("Qt小罗"), new Form());
//    this->addWidget(QStringLiteral("Qt小罗"), new Form());
//    this->addWidget(QStringLiteral("Qt小罗"), new Form());
//    this->addWidget(QStringLiteral("Qt小罗"), new Form());
//    this->addWidget(QStringLiteral("Qt小罗"), new Form());


}

//初始化窗体布局
void FuncViewerWidget::initWidget()
{
    auto verticalLayout = new QVBoxLayout();
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(verticalLayout);

    auto scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);

    verticalLayout->addWidget(scrollArea);

    m_pContentVBoxLayout = new QVBoxLayout();
    m_pContentVBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_pContentVBoxLayout->setSpacing(2);//设置上下间距

    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->setContentsMargins(0, 0, 0, 0);

    vBoxLayout->addLayout(m_pContentVBoxLayout);
    vBoxLayout->addStretch(1);

    QWidget *widget = new QWidget();
    widget->setLayout(vBoxLayout);

    scrollArea->setWidget(widget);
}
FuncViewerWidget::~FuncViewerWidget()
{
    delete ui;
}

//读取算子配置
void FuncViewerWidget::readWidgetConfig()
{
    QFileInfo fileInfo("configSobal.ini");
    if (!fileInfo.isFile())
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("错误"),
            QString::fromLocal8Bit("缺少算子配置文件！"));
        return;
    }
    QSettings settings("configSobal.ini", QSettings::IniFormat);
}

//创建显示的子窗体
void FuncViewerWidget::makePageWidget()
{

}

void FuncViewerWidget::addWidget(QString title, QWidget *widget)
{
    FuncViewerPage *page = new FuncViewerPage(this);
    page->addWidget(title, widget);

    m_pContentVBoxLayout->addWidget(page);
}

WIDGET_LIB_EXPORT FuncViewerWidget* __cdecl CreateWidget()
{
    return new FuncViewerWidget;
}

