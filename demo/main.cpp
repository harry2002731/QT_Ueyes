#include "lvmainmodel.h"
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
    a.setApplicationName("纳排标准分析系统");
    a.setQuitOnLastWindowClosed(true);
    a.setWindowIcon(QIcon(":/adsdemo/images/ads_icon2.svg"));



    QApplication app(argc, argv);

    // 创建一个QWidget窗口实例
    QWidget window;
    window.setWindowTitle("登录注册");
    window.resize(400, 800); // 设置窗口的尺寸

    // 创建一个垂直布局管理器
    QVBoxLayout *layout = new QVBoxLayout(&window);
    QQuickWidget* widget = new QQuickWidget();
    layout->addWidget(widget); // 将标签添加到布局中
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    LoginView::LVMainModel loginModel("exampleLogin");
    if (!loginModel.init(widget)) {
        return -1;
    }

    QString pathXML = ":/example.xml";
    if (argc > 1) {
        pathXML = QString(argv[1]);
    }

    if (!loginModel.setCounrySource(pathXML)) {
        return -2;
    }
    widget -> setSource(url);
    widget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    window.show();
    app.exec();

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
