#ifndef SYSINFOFETCHER_H
#define SYSINFOFETCHER_H
#include <QProcess>
#include <iostream>

#include <QTime>
#include <QTimer>
#include <QLabel>
#include <QFrame>
#include <QBoxLayout>
#include <QSettings>
#include <QDockWidget>
#include <QDebug>
#include <QResizeEvent>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QPointer>
#include "ads_globals.h"


#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    #include <QRegularExpression>
#endif

class ADS_EXPORT SysInfoFetcher
{
public:
    SysInfoFetcher();
    QString MemFetcher(QString imageName);
};

#endif // SYSINFOFETCHER_H
