#include "FuncViewerWidget.h"
#include "qdrag.h"
#include "qevent.h"
#include "qlistwidget.h"
#include "qmimedata.h"
#include "qpainter.h"
#include "ui_FuncViewerWidget.h"
#include "FuncViewerPage.h"
#include "Form.h"



FuncViewerWidget::FuncViewerWidget() :
    QWidget()
{
    this->initWidget();

    Form * form = new Form();
    form->layout()->addWidget(createLabel("ImageShowModel"));
    form->layout()->addWidget(createLabel("ImageLoaderModel"));
    form->layout()->addWidget(createLabel("ImageGrayModel"));

    this->addPageWidget(QStringLiteral("Qt"), form);
//    this->addWidget(QStringLiteral("Qt"), new Form());
//    this->addWidget(QStringLiteral("Qt"), new Form());
//    this->addWidget(QStringLiteral("Qt"), new Form());
//    this->addWidget(QStringLiteral("Qt"), new Form());
//    this->addWidget(QStringLiteral("Qt"), new Form());
//    connect(label,SIGNAL(mouseMove(QMouseEvent *)),this,SLOT(this->mouseMoveEvent(QMouseEvent *)));
}

DraggableLabel* FuncViewerWidget::createLabel(const QString& text) {
    static int labelCounter = 1;
    DraggableLabel* label = new DraggableLabel(text, this);
    label->setObjectName(QString("Label_%1").arg(labelCounter++));
    return label;
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

    m_widget->setLayout(vBoxLayout);

    scrollArea->setWidget(m_widget);

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

void FuncViewerWidget::addPageWidget(QString title, QWidget *widget)
{
    FuncViewerPage *page = new FuncViewerPage(this);
    page->addWidget(title, widget);
    m_pContentVBoxLayout->addWidget(page);
}

void FuncViewerWidget::mouseMoveEvent(QMouseEvent *e)
{
//    qDebug()<<"mouse move ";
//    QDrag *drag=new QDrag(this);
//    QMimeData *mimeData=new QMimeData;
//    mimeData->setText("test");
//    drag->setMimeData(mimeData);
//    QPixmap dragImg(2,56);
//    QPainter painter(&dragImg);
//    painter.setPen(QPen(Qt::red,2));
//    painter.drawLine(0,0,0,56);
//    drag->setPixmap(dragImg);
//    drag->exec(Qt::CopyAction|Qt::MoveAction);

}

WIDGET_LIB_EXPORT FuncViewerWidget*  __cdecl CreateWidget()
{
    return new FuncViewerWidget;
}

