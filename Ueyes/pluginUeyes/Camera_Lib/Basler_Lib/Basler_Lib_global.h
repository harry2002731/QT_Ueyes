#ifndef BASLER_LIB_GLOBAL_H
#define BASLER_LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BASLER_LIB_LIBRARY)
#  define BASLER_LIB_EXPORT Q_DECL_EXPORT
#else
#  define BASLER_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // BASLER_LIB_GLOBAL_H
