#include "pythonlib.h"
#include <iostream>

using namespace std;

PythonLib::PythonLib()
{
    Py_SetPythonHome(L"C:\\Program Files\\Python38");
    Py_Initialize();
    PyRun_SimpleString("import sys");
    std::string path = "sys.path.append(\"D:/Projects/PythonProjects/Medical_Classification/models/SVM/\")";
    const char* cstr_cmd = path.c_str();
    PyRun_SimpleString(cstr_cmd);
}
PythonLib::~PythonLib()
{
    Py_Finalize();
}
PyObject* PythonLib::callMethod(QString file_name, QString class_name, QString method_name, QString arg_str)
{
    PyObject* pModule = PyImport_ImportModule(file_name.toStdString().c_str()); //文件名
    PyObject* pDict = PyModule_GetDict(pModule); //获得的函数列

    //获取python类
    PyObject* pSvmAnalyzer = PyDict_GetItemString(pDict, class_name.toStdString().c_str());
    if (pSvmAnalyzer == NULL) {
        PyErr_Print();
    }

    PyObject* pInstanceSvmAnalyzer = PyObject_CallObject(pSvmAnalyzer,NULL);
    if (pInstanceSvmAnalyzer == NULL) {
        PyErr_Print();
    }

    PyObject *str = PyUnicode_FromString(arg_str.toStdString().c_str());
    PyObject* pValue = PyObject_CallMethod(pInstanceSvmAnalyzer, method_name.toStdString().c_str(),"(O)",str);

    return pValue;
}

void PythonLib::parsePyObject(PyObject* pValue, QVector<QPair<QVariant, QVariant>>& array2D)
{
//    QVector<QPair<QVariant, QVariant>> array2D;
    Py_ssize_t rows = PySequence_Size(pValue);
    for (Py_ssize_t i = 0; i < rows; ++i) {
        PyObject* row = PySequence_GetItem(pValue, i);
        if (!row) {
            PyErr_Print();
            continue;
        }

        // 获取每行的列数
        Py_ssize_t cols = PySequence_Size(row);
        float floatValue=0;
        string stringValue="";
        for (Py_ssize_t j = 0; j < cols; ++j) {
            PyObject* item = PySequence_GetItem(row, j);
            if (!item) {
                PyErr_Print();
                continue;
            }
            // 根据元素的类型进行处理
            if (PyFloat_Check(item)) {
                floatValue = PyFloat_AsDouble(item);
                std::cout << "floatValue: " << floatValue << " ";
            }
            else if (PyUnicode_Check(item)) {
                PyObject* str = PyUnicode_AsEncodedString(item, "GBK", "strict");
                stringValue = PyBytes_AS_STRING(str);
                stringValue  = QString::fromLocal8Bit(stringValue.data()).toUtf8().data();
                std::cout << "String: " << stringValue << " ";
                Py_DECREF(str);
            }
            else {
                std::cout << "Unknown type" << " ";
            }
        }
        if (floatValue && stringValue!="")
        {
            array2D.append(qMakePair<QString, double>(QString::fromStdString(stringValue), floatValue));
            QVariant firstVariant = array2D.at(0).first;
            QString intValue = firstVariant.value<QString>();
            std::cout << intValue.toStdString() << " ";

        }
    }

}
