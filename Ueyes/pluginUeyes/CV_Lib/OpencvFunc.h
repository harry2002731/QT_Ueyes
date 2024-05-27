#ifndef OPENCVFUNC_H
#define OPENCVFUNC_H
#include "OpencvFunc_globals.h"
#include <QWidget>

namespace Ui { class FuncViewerWidget; };

class OpencvFunc_EXPORT CVFunc: public QWidget
{
public:
    CVFunc(QWidget *parent = nullptr);
    Ui::FuncViewerWidget *ui;

    QWidget getUI();
};

#endif // OPENCVFUNC_H
