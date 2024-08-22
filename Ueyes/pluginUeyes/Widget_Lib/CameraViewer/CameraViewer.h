#ifndef CAMERAVIEWER_H
#define CAMERAVIEWER_H


#include <QWidget>

class QMenu;
class QLabel;
class QGridLayout;
class VideoBox;
#include "Basler_Lib/Basler_Lib.h"
#include "Hikvision_Lib/Hikvision_Lib.h"
#include "mWindow.h"

#ifdef quc
class Q_DECL_EXPORT CameraViewer : public QWidget
#else

class CameraViewer : public QWidget
#endif
{
    Q_OBJECT

public:
    explicit CameraViewer(QWidget *parent = 0);
    QLabel *widget_0_label;
    QLabel *widget_1_label;
    int count = 0;
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    bool videoMax;              //是否最大化
    int videoCount;             //视频通道个数
    QString videoType;          //当前画面类型
    QMenu *videoMenu;           //右键菜单
    QMenu *cameraMenu;           //右键菜单

    QAction *cameraActionFull1;
    QAction *cameraActionFull2;

    QAction *actionFull;        //全屏动作
    QAction *actionPoll;        //轮询动作

    QGridLayout *gridLayout;    //通道表格布局
    QWidgetList widgets;        //视频控件集合
    VideoBox *videoBox;         //通道布局类
    QPixmap pix;
    MainWindow w;
    MainWindow w2;

    QtHik::Hikvision_Lib hik;
public:
    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

private slots:
    void initControl();
    void initForm();
    void initMenu();
    void full();
    void configCamera();
    void poll();
//    void test(QImage img);
public slots:
    void test(QImage iii);

private slots:
    void play_video_all();
    void snapshot_video_one();
    void snapshot_video_all();

signals:
    //全屏切换信号
    void fullScreen(bool full);
};


#endif // CAMERAVIEWER_H
