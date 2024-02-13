 #include "OpencvFunc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CVFunc w;
    w.show();
    return a.exec();
}
