#ifndef PYTHONLIB_H
#define PYTHONLIB_H
#include <Python.h>

#include "Python_Lib_global.h"
#include <QString>
#include <QVector>
#include <QPair>
#include <QVariant>

class PYTHON_LIB_EXPORT PythonLib
{
public:
    PythonLib();
    PyObject* callMethod(QString file_name, QString class_name, QString method_name, QString arg_str);
    void parsePyObject(PyObject* pValue);
private slots:

};

#endif // PYTHONLIB_H
