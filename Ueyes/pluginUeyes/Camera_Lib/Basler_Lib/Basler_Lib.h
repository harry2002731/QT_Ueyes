#ifndef BASLER_LIB_H
#define BASLER_LIB_H

#include <QObject>
#include "Basler_Lib_global.h"
#include "QtGui/qimage.h"
#include <QLabel>
#include "qtmetamacros.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class BASLER_LIB_EXPORT Basler_Lib  : public QObject
{
    Q_OBJECT
public:
    Basler_Lib();
    cv::VideoCapture cap;
    int count = 0;
    cv::Mat frame;
    QImage image;
    bool is_init_camera = false;
    void initCamera();
public slots:
    void readImage();

    void readDesktopCameraTest();

signals:
    void sigCurrentImage(QImage iii);

//    void sigCurrentImage(QImage img);

};

#endif // BASLER_LIB_H
