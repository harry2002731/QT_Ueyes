#ifndef SQLLITE_LIB_GLOBAL_H
#define SQLLITE_LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLLITE_LIB_LIBRARY)
#  define SQLLITE_LIB_EXPORT Q_DECL_EXPORT
#else
#  define SQLLITE_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLLITE_LIB_GLOBAL_H
