#define PY_SSIZE_T_CLEAN
#include <python/Python.h>

static PyObject* mozilla_execute(PyObject* self, PyObject* args)
{
 char* script = NULL;

 if(!PyArg_ParseTuple(args, "s", &script))
    return NULL;

 printf(script);
 Py_RETURN_NONE;
}

static PyMethodDef mozilla_methods[] =
{
 {"execute", mozilla_execute, METH_VARARGS, "Execute a JavaScript"},
 {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mozilla_module =
{
 PyModuleDef_HEAD_INIT,
 "spidermonkey",
 "Python interface to Mozilla SpiderMonkey library",
 -1,
 mozilla_methods
};

PyMODINIT_FUNC PyInit_spidermonkey(void)
{
 return PyModule_Create(&mozilla_module);
}