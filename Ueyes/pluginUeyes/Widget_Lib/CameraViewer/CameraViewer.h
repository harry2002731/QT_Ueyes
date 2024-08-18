#ifndef CAMERAVIEWER_H
#define CAMERAVIEWER_H

/**
 * 视频监控画面控件 整理:feiyangqingyun(QQ:517216493) 2019-04-11
 * 1. 可设定视频通道数量。
 * 2. 支持双击最大化再次双击还原。
 * 3. 支持4/6/8/9/13/16/25/36/64等通道布局。
 * 4. 内置了选中边框高亮等样式。
 * 5. 通用的视频通道布局盒子类，方便拓展其他布局。
 */

#include <QWidget>

class QMenu;
class QLabel;
class QGridLayout;
class VideoBox;
#include "../../Camera_Lib/Basler_Lib/Basler_Lib.h"
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
    int count = 0;
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    bool videoMax;              //是否最大化
    int videoCount;             //视频通道个数
    QString videoType;          //当前画面类型
    QMenu *videoMenu;           //右键菜单
    QAction *actionFull;        //全屏动作
    QAction *actionPoll;        //轮询动作

    QGridLayout *gridLayout;    //通道表格布局
    QWidgetList widgets;        //视频控件集合
    VideoBox *videoBox;         //通道布局类
    QPixmap pix;
public:
    QSize sizeHint()            const;
    QSize minimumSizeHint()     const;

private slots:
    void initControl();
    void initForm();
    void initMenu();
    void full();
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
