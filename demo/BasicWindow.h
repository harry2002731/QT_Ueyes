#ifndef BASICWINDOW_H
#define BASICWINDOW_H
#include "DockManager.h"

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QFrame>
#include <QTreeView>
#include <QFileSystemModel>
#include <QBoxLayout>
#include <QSettings>
#include <QDockWidget>
#include <QDebug>
#include <QResizeEvent>
#include <QAction>
#include <QWidgetAction>
#include <QComboBox>
#include <QInputDialog>
#include <QRubberBand>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QScreen>
#include <QStyle>
#include <QMessageBox>
#include <QMenu>
#include <QToolButton>
#include <QToolBar>
#include <QPointer>
#include <QMap>
#include <QElapsedTimer>
#include <QQuickWidget>


#include "qstackedwidget.h"
#include "qsettings.h"
#include "ImageViewer.h"
#include "videopanel.h"
#include <windows.h>
#include "SqlInterface.h"
#include <QPluginLoader>

#include <QStandardItemModel>
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
#include <QRandomGenerator>
#endif

#ifdef Q_OS_WIN
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <QAxWidget>
#endif
#endif
class BasicWindow : public ads::CDockManager
{
    Q_OBJECT

public:
    BasicWindow(QWidget *parent,QString name);
    QString win_name;
public:
    //基础操作
    virtual void  createContent();
    void saveDockState();
    void saveDockPerspectives();
    void restoreDockState();
    void restoreDockPerspectives();
    void applyVsStyle();


    //基础窗体
    virtual ads::CDockWidget*  createFileSystemTreeDockWidget();
    virtual ads::CDockWidget*  createLabelDockWidget();
    virtual ads::CDockWidget*  createEditorWidget();
    virtual ads::CDockWidget*  createCameraViewerWidget();
    virtual ads::CDockWidget*  createTableWidget();
    virtual ads::CDockWidget*  createImageViewerWidget();
    virtual ads::CDockWidget*  createQQuickWidget();
    virtual ads::CDockWidget*  createTest();
    virtual ads::CDockWidget* test();
    virtual ads::CDockWidget* loadPlugin();

    DeclareInterface* m_pInterface = nullptr;  //获取插件类型



};

#endif // BASICWINDOW_H
