#define PY_SSIZE_T_CLEAN
#include <python/Python.h>

static PyObject* mozilla_execute(PyObject* self, PyObject* args)
{
 char* script = NULL;
 PyObject* context = NULL;

 if(!PyArg_ParseTuple(args, "sO", &script, &context))
    return NULL;

 PyObject* globals = PyObject_GetAttrString(context, "globals");
 if(!PyDict_Check(globals))
    return NULL;
 PyObject* print = PyDict_GetItemString(globals, "print");

 PyObject *key, *value;
 Py_ssize_t pos = 0;
 while(PyDict_Next(globals, &pos, &key, &value))
     {
     PyObject* pargs = PyTuple_New(1);
     Py_INCREF(key);
     PyTuple_SetItem(pargs, 0, key);
     Py_XDECREF(PyObject_CallObject(print, pargs));
     Py_DECREF(pargs);
     }

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