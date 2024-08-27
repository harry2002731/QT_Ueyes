#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include "Hikvision_Lib/Hikvision_Lib.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setWinId(WId MainWndID);

    ~MainWindow();
private slots:
    void on_EnumButton_clicked();

    void on_OpenButton_clicked();

    void on_CloseButton_clicked();

    void on_StartGrabbingButton_clicked();

    void on_StopGrabbingButton_clicked();

    void on_SaveBmpButton_clicked();

    void on_HardwareRadioButton_clicked();

    void on_ContinuesRadioButton_clicked();

    void on_SetParamButton_clicked();

    void on_GetParamButton_clicked();

private:
    Ui::MainWindow *ui;
    WId wndID;
    //海康威视接口对象
private:
    QtHik::Hikvision_Lib hik;


};

#endif // MWINDOW_H
