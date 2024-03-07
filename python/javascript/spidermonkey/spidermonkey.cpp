#define PY_SSIZE_T_CLEAN
#include <python/Python.h>

static PyObject* mozilla_execute(PyObject* self, PyObject* args)
{
 char* script = NULL;
 PyObject* context = NULL;

 if(!PyArg_ParseTuple(args, "sO", &script, &context))
    return NULL;

 if(!PyDict_Check(context))
    return NULL;

 PyObject *key, *value;
 Py_ssize_t pos = 0;
 while(PyDict_Next(context, &pos, &key, &value))
     {
     wchar_t* str = PyUnicode_AsWideCharString(key, NULL);
     printf("%ls\n", str);
     PyMem_Free(str);
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