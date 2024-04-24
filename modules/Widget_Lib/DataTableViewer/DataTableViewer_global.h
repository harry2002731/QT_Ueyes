#ifndef DATATABLEVIEWER_GLOBAL_H
#define DATATABLEVIEWER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATATABLEVIEWER_LIBRARY)
#  define DATATABLEVIEWER_EXPORT Q_DECL_EXPORT
#else
#  define DATATABLEVIEWER_EXPORT Q_DECL_IMPORT
#endif

#endif // DATATABLEVIEWER_GLOBAL_H