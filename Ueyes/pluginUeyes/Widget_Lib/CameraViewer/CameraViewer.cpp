#pragma execution_character_set("utf-8")

#include "CameraViewer.h"
#include "videobox.h"
#include "qevent.h"
#include "qmenu.h"
#include "qlayout.h"
#include "qlabel.h"
#include "qtimer.h"
#include "Basler_Lib/Basler_Lib.h"
#include "Hikvision_Lib/Hikvision_Lib.h"
CameraViewer::CameraViewer(QWidget* parent) : QWidget(parent)
{
    this->initControl();
    this->initForm();
    this->initMenu();
    QTimer::singleShot(1000, this, SLOT(play_video_all()));
}

bool CameraViewer::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        QLabel *widget = (QLabel *) watched;
        if (!videoMax) {
            videoMax = true;
            videoBox->hide_video_all();
            gridLayout->addWidget(widget, 0, 0);
            widget->setVisible(true);
        } else {
            videoMax = false;
            videoBox->show_video_all();
        }
        widget->setFocus();
    } else if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        if (mouseEvent->button() == Qt::RightButton) {
            cameraMenu->exec(QCursor::pos());
        }
    }

    return QWidget::eventFilter(watched, event);
}

QSize CameraViewer::sizeHint() const
{
    return QSize(800, 600);
}

QSize CameraViewer::minimumSizeHint() const
{
    return QSize(80, 60);
}

void CameraViewer::initControl()
{
    gridLayout = new QGridLayout;
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(gridLayout);
}

void CameraViewer::initForm()
{
    //设置样式表
#ifndef no_style
    QStringList qss;
    qss.append("QFrame{border:2px solid #000000;}");
    qss.append("QLabel{font:75 25px;color:#F0F0F0;border:2px solid #AAAAAA;background:#303030;}");
    qss.append("QLabel:focus{border:2px solid #00BB9E;background:#555555;}");
    this->setStyleSheet(qss.join(""));
#endif

    videoMax = false;
    videoCount = 64;
    videoType = "1_2";

    for (int i = 0; i < videoCount; ++i) {
        QLabel *widget = new QLabel;
        widget->setObjectName(QString("video%1").arg(i + 1));
        widget->installEventFilter (this);
        widget->setFocusPolicy(Qt::StrongFocus);
        widget->setAlignment(Qt::AlignCenter);
        widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        //二选一可以选择显示文字,也可以选择显示背景图片
        widget->setText(QString("通道 %1").arg(i + 1));

        if (i == 0)
        {
            widget_0_label = new QLabel();
            widget->setLayout(new QVBoxLayout());
            widget->layout()->addWidget(widget_0_label);
//            Basler_Lib * basler = new Basler_Lib();
//            bool success = connect(basler, &Basler_Lib::sigCurrentImage,this, &CameraViewer::test);
//            basler->readImage();
        }
        else if(i == 1)
        {
            widget_1_label = new QLabel();
            widget->setLayout(new QVBoxLayout());
            widget->layout()->addWidget(widget_1_label);
        }
        else
        {
            widget->setLayout(new QVBoxLayout());
            widget->layout()->addWidget(new QLabel());
        }
        //widget->setPixmap(QPixmap(":/bg_novideo.png"));
        widgets << widget;
    }
}

void CameraViewer::initMenu()
{
    videoMenu = new QMenu(this);
    cameraMenu = new QMenu(this);
    cameraActionFull1 = new QAction("选择输入源1", cameraMenu);
    cameraActionFull2 = new QAction("选择输入源2", cameraMenu);

    connect(cameraActionFull1, SIGNAL(triggered(bool)), this, SLOT(configCamera()));
    connect(cameraActionFull2, SIGNAL(triggered(bool)), this, SLOT(configCamera()));

    cameraMenu->addAction(cameraActionFull1);
    cameraMenu->addAction(cameraActionFull2);

    //单独关联信号槽
    actionFull = new QAction("切换全屏模式", videoMenu);
    connect(actionFull, SIGNAL(triggered(bool)), this, SLOT(full()));
    actionPoll = new QAction("启动轮询视频", videoMenu);
    connect(actionPoll, SIGNAL(triggered(bool)), this, SLOT(poll()));

    //通过QAction类方式添加子菜单
    videoMenu->addAction(actionFull);
    videoMenu->addAction(actionPoll);
    videoMenu->addSeparator();

    //直接通过文字的形式添加子菜单
    videoMenu->addAction("截图当前视频", this, SLOT(snapshot_video_one()));
    videoMenu->addAction("截图所有视频", this, SLOT(snapshot_video_all()));
    videoMenu->addSeparator();

    //实例化通道布局类
    videoBox = new VideoBox(this);
    QList<bool> enable;
    enable << true << true << true << true << true << true << true << true << true;

//    videoBox->initCameraMenu(cameraMenu, enable);
//    videoBox->initMenu(videoMenu, enable);
    videoBox->setVideoType(videoType);
    videoBox->setLayout(gridLayout);
    videoBox->setWidgets(widgets);
    videoBox->show_video_all();
}
void CameraViewer::test(QImage img)
{
    auto aaa = img.size();
    pix = QPixmap::fromImage(img);
    widget_0_label->setPixmap(pix);
    std::cout<<"recieve"<<count<<std::endl;
    count+=1;
}
void CameraViewer::configCamera()
{
    HWND MainWndID;
    QAction *action = qobject_cast<QAction *>(sender());
    if (action == cameraActionFull1) {
        w.setFixedSize(300,400);
        w.setWindowTitle("窗体1相机设置");
        MainWndID = (HWND)widget_0_label->winId();
        w.setWinId(MainWndID);
        w.show();
        w.adjustSize();

    } else if (action == cameraActionFull2) {
        w2.setFixedSize(300,400);
        w2.setWindowTitle("窗体2相机设置");
        MainWndID = (HWND)widget_1_label->winId();
        w2.setWinId(MainWndID);
        w2.show();
        w2.adjustSize();

    }
}
void CameraViewer::full()
{
    if (actionFull->text() == "切换全屏模式") {
        emit fullScreen(true);
        actionFull->setText("切换正常模式");
    } else {
        emit fullScreen(false);
        actionFull->setText("切换全屏模式");
    }

    //执行全屏处理
}

void CameraViewer::poll()
{
    if (actionPoll->text() == "启动轮询视频") {
        actionPoll->setText("停止轮询视频");
    } else {
        actionPoll->setText("启动轮询视频");
    }

    //执行轮询处理
}

void CameraViewer::play_video_all()
{

}

void CameraViewer::snapshot_video_one()
{

}

void CameraViewer::snapshot_video_all()
{

}

