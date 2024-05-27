#ifndef QtPluginsManager_H
#define QtPluginsManager_H

#include "pluginmanager_global.h"
#include "QtPluginsManagerprivate.h"

class PLUGINMANAGER_EXPORT QtPluginsManager
{
public:
    QtPluginsManager();

    void loadAllPlugins();
    void unloadAllPlugins();

    void loadPlugin(const QString &filePath);
    void scanPlugin(const QString &filePath);

    void unloadPlugin(const QString &filePath);

private:
    QtPluginsManagerPrivate* d;
};

#endif // QtPluginsManager_H
