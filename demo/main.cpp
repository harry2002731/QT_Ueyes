#include <MainWindow.h>
#include <QString>
#include <QFile>
#include <QApplication>
#include <QDebug>

#include <memory>

#include <QQuickWidget>

int main(int argc, char *argv[])
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if QT_VERSION >= 0x050600
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#endif
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);//解决需要openGL的问题

    std::shared_ptr<int> b;
    QApplication a(argc, argv);
    a.setApplicationName("Advanced Docking System Demo");
    a.setQuitOnLastWindowClosed(true);
    a.setWindowIcon(QIcon(":/adsdemo/images/ads_icon2.svg"));

    CMainWindow mw;
    mw.show();
//    mainWindow.showMaximized(); // 打开时最大化

    QFile StyleSheetFile(":/adsdemo/app.css");
    StyleSheetFile.open(QIODevice::ReadOnly);
    QTextStream StyleSheetStream(&StyleSheetFile);
    a.setStyleSheet(StyleSheetStream.readAll());
    StyleSheetFile.close();
    return a.exec();
}
