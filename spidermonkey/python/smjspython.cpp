#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

static PyObject* smjs_open_context(PyObject* module, PyObject* args)
{
 std::cout << "smjs_open_context\n";
 Py_RETURN_NONE;
}

static PyObject* smjs_close_context(PyObject* module, PyObject* args)
{
 std::cout << "smjs_close_context\n";
 Py_RETURN_NONE;
}

static PyObject* smjs_execute(PyObject* module, PyObject* args)
{
 std::cout << "smjs_execute\n";
 Py_RETURN_NONE;
}

static PyObject* smjs_shutdown(PyObject* module, PyObject* args)
{
 std::cout << "smjs_shutdown\n";
 Py_RETURN_NONE;
}

static PyMethodDef smjs_methods[] =
{
 {"open_context", smjs_open_context, METH_VARARGS, "Opens a SpiderMonkey JavaScript context"},
 {"close_context", smjs_close_context, METH_VARARGS, "Closes a SpiderMonkey JavaScript context"},
 {"execute", smjs_execute, METH_VARARGS, "Execute a JavaScript"},
 {"shutdown", smjs_shutdown, METH_VARARGS, "Shutdowns the SpiderMoney JavaScript engine"},
 {NULL, NULL, 0, NULL}
};

static struct PyModuleDef smjs_module =
{
 PyModuleDef_HEAD_INIT,
 "smjs",
 "Python interface to Mozilla SpiderMonkey library",
 -1,
 smjs_methods
};

PyMODINIT_FUNC PyInit_smjs(void)
{
 return PyModule_Create(&smjs_module);
}