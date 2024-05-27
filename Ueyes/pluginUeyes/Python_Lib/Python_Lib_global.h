#ifndef PYTHON_LIB_GLOBAL_H
#define PYTHON_LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PYTHON_LIB_LIBRARY)
#  define PYTHON_LIB_EXPORT Q_DECL_EXPORT
#else
#  define PYTHON_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // PYTHON_LIB_GLOBAL_H
