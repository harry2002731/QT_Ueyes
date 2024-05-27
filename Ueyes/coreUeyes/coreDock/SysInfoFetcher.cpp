#include "SysInfoFetcher.h"



//用于获取进程内存占用
SysInfoFetcher::SysInfoFetcher()
{
    
}

QString SysInfoFetcher::MemFetcher(QString imageName)
{
#ifdef Q_OS_WIN
#if (QT_VERSION > QT_VERSION_CHECK(6, 0, 0))
    QStringList sl;
    QProcess p;
    QString argms = "Imagename eq ";
    argms = argms + imageName;

    sl << "/v" <<  "/fi" << argms;
    p.start("tasklist",sl);
    p.waitForFinished();
    QString result = QString::fromLocal8Bit(p.readAllStandardOutput());
    p.close();
    result = result.replace(",","");
    QRegularExpression rx("(\\d+)(\\s)(K)");
    QRegularExpressionMatch match = rx.match(result);
    QString usedMem("");
    if(match.hasMatch())
    {
        usedMem = match.captured(0);
    }
    // 截取K前面的字符串，转换为数字，供换算单位使用。
    usedMem = usedMem.left(usedMem.length() - 1);
    QString memoryNum = QString::number(usedMem.toDouble()/1024,'g',4) + "M";     // 换算为MB的单位
    return memoryNum;
#endif
#endif
}
