#ifndef WIDGET_LIB_GLOBAL_H
#define WIDGET_LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WIDGET_LIB_LIBRARY)
#  define WIDGET_LIB_EXPORT Q_DECL_EXPORT
#else
#  define WIDGET_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // WIDGET_LIB_GLOBAL_H
