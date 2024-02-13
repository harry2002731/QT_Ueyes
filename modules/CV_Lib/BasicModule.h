#ifndef BASICMODULE_H
#define BASICMODULE_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>

#include <QTime>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QVector>
using namespace cv;

enum ModuleStatus {
    NotExecuted, //未执行
    Running, // 正在运行
    Success, // 执行通过
    Failure  // 执行失败
};



class BasicModule : public QObject
{
    Q_OBJECT
public:
    BasicModule();

protected:
    uint id; //模块ID,即在列表中第几个位置
    QString name; //模块名称
    ModuleStatus state; //模块当前状态
    double costTime; //模块执行时间
    cv::Mat* inputPicPtr; //输入图像指针
    cv::Mat* outputPicPtr; //输出图像指针
    QWidget* ui; //ui界面布局
    QTableWidget* qTableWidget; //表格布局，用于调试可视化，与ui布局独立开来
    QString log; //模块运行日志

    bool isLogCheckingEnabled; // 是否开启日志输出
    bool isDataCheckingEnabled; // 是否开启数据可视化

public:
    uint getId();
    QString getName();
    ModuleStatus getState();
    double getCostTime();
    cv::Mat* getInputPicPtr();
    cv::Mat* getOutputPicPtr();
    QWidget* getUi();
    QTableWidget* getQTableWidget();
    QString getLog();


    void setId(uint id);
    void setName(QString name);
    void setIsLogCheckingEnabled(bool temp);
    void setIsDataCheckingEnabled(bool temp);
    void setInputPicPtr(cv::Mat* picPtr);
    void updateState(ModuleStatus state);

    void drawTable();


};

#endif // BASICMODULE_H
