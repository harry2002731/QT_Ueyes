#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H
#include <BasicWindow.h>
#include <QString>
#include <QWidget>

class WelcomeWindow : public BasicWindow
{
    Q_OBJECT
public:
    WelcomeWindow(QWidget *parent,QString name);
    void createContent() override;
};

#endif // WELCOMEWINDOW_H
