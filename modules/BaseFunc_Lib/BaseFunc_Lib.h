#ifndef BASEFUNC_LIB_H
#define BASEFUNC_LIB_H

#include "BaseFunc_Lib_global.h"
//#include <windows.h>
#include <Qstring>
#include <QLibrary>
#include <windows.h>

//#include <string.h>
class Q_DECL_EXPORT BaseFunc_Lib
{
public:
    BaseFunc_Lib();


    template<typename FuncType>
    FuncType loadLibFunc(QString lib_name,const char* class_name)
    {
        typedef FuncType (*CREATE_WIDGET) ();
        QLibrary mylib(lib_name);
        if (mylib.load())
        {
            FuncType (*func)()  = reinterpret_cast<FuncType (*)()>(mylib.resolve(class_name));
            FuncType pMath = func();
            return pMath;
        }
    }
};

#endif // BASEFUNC_LIB_H
