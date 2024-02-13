#ifndef OPENCVFUNC_GLOBALS_H
#define OPENCVFUNC_GLOBALS_H

//#include <QtCore/qglobal.h>

#if defined(OpencvFunc_LIBRARY)
#  define OpencvFunc_EXPORT Q_DECL_EXPORT
#else
#  define OpencvFunc_EXPORT Q_DECL_IMPORT
#endif

#endif // OPENCVFUNC_GLOBALS_H
