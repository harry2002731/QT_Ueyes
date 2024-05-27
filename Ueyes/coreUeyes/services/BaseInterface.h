#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H
#include <QtPlugin>
#include <QtCore>
#include "qglobal.h"

#define BaseInterface_iid "Examples.Plugin.TestInterface"


//基类接口

class BaseInterface
{
public:
    virtual ~BaseInterface() {}


};


#define SQLITESTUDIO_PLUGIN(file)\
    Q_PLUGIN_METADATA(IID BaseInterface_iid FILE file) \
    Q_INTERFACES(BaseInterface)

Q_DECLARE_INTERFACE(BaseInterface, BaseInterface_iid)

#endif // BASEINTERFACE_H
