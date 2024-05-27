#ifndef GUI_UEYES_GLOBAL_H
#define GUI_UEYES_GLOBAL_H
#include <QtCore/qglobal.h>


#if defined(GUI_UEYES_LIBRARY)
#  define GUI_UEYES_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define GUI_UEYES_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

#endif // GUI_UEYES_GLOBAL_H

