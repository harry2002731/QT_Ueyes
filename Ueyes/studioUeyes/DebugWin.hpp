#ifndef DEBUGWIN_HPP
#define DEBUGWIN_HPP

#include <QMainWindow>

class DebugWin : public QMainWindow
{
public:
    DebugWin(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *event) override ;
};

#endif // DEBUGWIN_HPP
