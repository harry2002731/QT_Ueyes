#ifndef QTPLUGINSMANAGERPRIVATE_H
#define QTPLUGINSMANAGERPRIVATE_H
#include <QHash>
#include <QVariant>
#include <QPluginLoader>

struct QtPlugin
{
//    QString m_path;
    QVariant m_names;
    QVariant m_versions;
    QVariantList m_dependencies;
    QPluginLoader * m_loaders;
};

class QtPluginsManagerPrivate
{
public:
    QtPluginsManagerPrivate();
public:
    //插件依赖检测
    bool check(const QString &filepath);
    QHash<QString,QtPlugin> m_plugins;
//    QHash<QString, QVariant> m_names; //插件路径--插件名称
//    QHash<QString, QVariant> m_versions; //插件路径--插件版本
//    QHash<QString, QVariantList>m_dependencies; //插件路径--插件额外依赖的其他插件
//    QHash<QString, QPluginLoader *>m_loaders; //插件路径--QPluginLoader实例

};

#endif // QTPLUGINSMANAGERPRIVATE_H
