#include "BasicModule.h"

BasicModule::BasicModule()
{
    this->ui = new QWidget();
    this->qTableWidget = new QTableWidget();
    this->isLogCheckingEnabled = false; // 是否开启日志输出
    this->isDataCheckingEnabled = false; // 是否开启数据可视化
}


uint BasicModule::getId()
{
    return this->id;
}
QString BasicModule::getName()
{
    return this->name;
}
ModuleStatus BasicModule::getState()
{
    return this->state;
}
double BasicModule::getCostTime()
{
    return this->costTime;
}
cv::Mat* BasicModule::getOutputPicPtr()
{
    return this->outputPicPtr;
}
cv::Mat* BasicModule::getInputPicPtr()
{
    return this->inputPicPtr;
}
QWidget* BasicModule::getUi()
{
    return this->ui;
}
QTableWidget* BasicModule::getQTableWidget()
{
    return this->qTableWidget;
}


void BasicModule::setId(uint id)
{
    this->id = id;
}
void BasicModule::setName(QString name)
{
    this->name = name;
}
void BasicModule::setIsLogCheckingEnabled(bool temp)
{
    this->isLogCheckingEnabled = temp;
}
void BasicModule::setIsDataCheckingEnabled(bool temp)
{
    this->isDataCheckingEnabled = temp;
}
void BasicModule::setInputPicPtr(cv::Mat* picPtr)
{
    this->inputPicPtr = picPtr;
}


void BasicModule::updateState(ModuleStatus state)
{
    this->state = state;
}

void BasicModule::drawTable()
{

}
