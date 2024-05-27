#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QVector>
using namespace cv;






Mat gray_to_level(Mat gray)//灰度直方图函数
{
    QVector<int> pixel(256,0);

    for(int i = 0 ; i < gray.rows ; i++)
        for(int j = 0 ; j < gray.cols ; j++){
            pixel[gray.at<uchar>(i,j)]++;
        }

    Mat gray_level;
    gray_level.create(350, 256, CV_8UC1);

    int max_rows = 0;
    for(int i = 0;i <= 255;i++){
        if(pixel[i] > max_rows){
            max_rows = pixel[i];
        }
    }

    for(int i = 0;i < 256;i++){
        for(int j = 0;j < 350 ; j++){
            gray_level.at<uchar>(j,i) = 255;
        }
    }

    for(int i = 0;i < 256;i++){
        for(int j = 0;j < 350 - int(320.*float(pixel[i])/float(max_rows)) ; j++){
            gray_level.at<uchar>(j,i) = 0;
        }
    }

    return gray_level;

}
