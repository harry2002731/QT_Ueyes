#ifndef HIKVISION_LIB_GLOBAL_H
#define HIKVISION_LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HIKVISION_LIB_LIBRARY)
#  define HIKVISION_LIB_EXPORT Q_DECL_EXPORT
#else
#  define HIKVISION_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // HIKVISION_LIB_GLOBAL_H