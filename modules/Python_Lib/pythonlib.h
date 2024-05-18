#ifndef PYTHONLIB_H
#define PYTHONLIB_H

#include "Python_Lib_global.h"
#include <QString>
#include <QVector>
#include <QPair>
#include <QVariant>
#include "Python.h"

class PYTHON_LIB_EXPORT PythonLib
{
public:
    PythonLib();
    ~PythonLib();
    PyObject* callMethod(QString file_name, QString class_name, QString method_name, QString arg_str);
    void parsePyObject(PyObject* pValue, QVector<QPair<QVariant, QVariant>>& array2D);

private slots:

};

#endif // PYTHONLIB_H
