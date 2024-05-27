#include "QtPluginsManager.h"
#include "qjsonarray.h"
#include <QDir>
#include <QApplication>
#include <QLibrary>
#include <QPluginLoader>
//#include "plugininterface.h"

QtPluginsManager::QtPluginsManager()
{
    d = new QtPluginsManagerPrivate();
}
void QtPluginsManager::loadAllPlugins()
{
    QDir pluginsdir = QDir(qApp->applicationDirPath());
    pluginsdir.cd("plugins");

    QFileInfoList pluginsInfo = pluginsdir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    //初始化插件中的元数据
    for(QFileInfo fileinfo : pluginsInfo)
        scanPlugin(fileinfo.absoluteFilePath());

    //加载插件
    for(QFileInfo fileinfo : pluginsInfo)
        loadPlugin(fileinfo.absoluteFilePath());
}
void QtPluginsManager::unloadAllPlugins()
{
    for(QString filePath : d->m_plugins.keys())
        unloadPlugin(filePath);
}



void QtPluginsManager::scanPlugin(const QString &filePath)
{
    //判断是否为库（后缀有效性）
    if(!QLibrary::isLibrary(filePath))
        qDebug()<<"It is not a correct path to load plugin.";
    //获取元数据
    QPluginLoader *loader = new QPluginLoader(filePath);
    QJsonObject json = loader->metaData().value("MetaData").toObject();

    QtPlugin plugin;
    plugin.m_names = json.value("name").toVariant();
    plugin.m_versions = json.value("version").toVariant();
    plugin.m_dependencies = json.value("dependencies").toArray().toVariantList();
    delete loader;

}
void QtPluginsManager::loadPlugin(const QString &filePath)
{
//    if(!QLibrary::isLibrary(filePath))
//        return;

//    //检测依赖
//    if(!d->check(filePath))
//        return;

//    //加载插件
//    QPluginLoader *loader = new QPluginLoader(filePath);
//    if(loader->load())
//    {
//        // 如果继承自 Plugin，则认为是自己的插件（防止外部插件注入）。
//        PluginInterface *plugin = qobject_cast<PluginInterface *>(loader->instance());
//        if(plugin)
//        {
//            d->m_loaders.insert(filePath, loader);
//            plugin->connectTosendMsgToManager(this, SLOT(recMsgFromManager(PluginMetaData&)), true);
//        }
//        else
//        {
//            delete loader;
//            loader = nullptr;
//        }
//    }
}

void QtPluginsManager::unloadPlugin(const QString &filePath)
{

}
