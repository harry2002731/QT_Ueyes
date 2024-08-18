#include "DebugWin.hpp"
#include "qevent.h"

DebugWin::DebugWin(QWidget *parent)
{

}
void DebugWin::closeEvent(QCloseEvent *event) {

    event->ignore();
    this->hide();

}
