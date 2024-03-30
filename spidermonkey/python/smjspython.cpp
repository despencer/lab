#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <smjs.h>

static bool smjsinit = false;
static const char* smattrname = "sm";
static PyObject* smerrorclass = NULL;

static PyObject* smjs_open_context(PyObject* module, PyObject* args)
{
   // The SpiderMonkey engine has not yet initialized
 if(!smjsinit)
    {
    SMContext::init();
    smjsinit = true;

    smerrorclass = PyErr_NewException("smjs.jserror", NULL, NULL);
    Py_XINCREF(smerrorclass);
    }

 PyObject* context = NULL;
 if(!PyArg_ParseTuple(args, "O", &context))
    return NULL;

 SMContext* sm = SMContext::open();
 if(sm == NULL) return NULL;

 PyObject* capsule = PyCapsule_New(sm, NULL, NULL);
 if(capsule == NULL)
    { sm->close(); delete sm; return NULL; }

 if(PyObject_SetAttrString(context, smattrname, capsule) != 0)
    { sm->close(); delete sm; return NULL; }

 Py_RETURN_NONE;
}

static SMContext* getcontext(PyObject* context)
{
 PyObject* capsule = PyObject_GetAttrString(context, smattrname);
 if(capsule == NULL) return NULL;

 return (SMContext*)PyCapsule_GetPointer(capsule, NULL);
}

static PyObject* smjs_close_context(PyObject* module, PyObject* args)
{
 PyObject* context = NULL;
 if(!PyArg_ParseTuple(args, "O", &context))
    return NULL;

 SMContext* sm = getcontext(context);
 if(sm == NULL) return NULL;

 sm->close(); delete sm;
 PyObject_SetAttrString(context, smattrname, NULL);

 Py_RETURN_NONE;
}

static PyObject* smjs_execute(PyObject* module, PyObject* args)
{
 PyObject* context = NULL;
 char* script = NULL;
 if(!PyArg_ParseTuple(args, "Os", &context, &script))
    return NULL;

 SMContext* sm = getcontext(context);
 if(sm == NULL) return NULL;

 if(!sm->evaluate(script))
    {
    PyErr_SetString(smerrorclass, sm->geterror().c_str());
    return NULL;
    }

 Py_RETURN_NONE;
}

static PyObject* smjs_add_global(PyObject* module, PyObject* args)
{
 Py_RETURN_NONE;
}

static PyObject* smjs_shutdown(PyObject* module, PyObject* args)
{
 Py_XDECREF(smerrorclass);
 Py_CLEAR(smerrorclass);

 if(smjsinit)
     SMContext::shutdown();
 Py_RETURN_NONE;
}

static PyMethodDef smjs_methods[] =
{
 {"open_context", smjs_open_context, METH_VARARGS, "Opens a SpiderMonkey JavaScript context"},
 {"close_context", smjs_close_context, METH_VARARGS, "Closes a SpiderMonkey JavaScript context"},
 {"execute", smjs_execute, METH_VARARGS, "Execute a JavaScript"},
 {"add_global", smjs_add_global, METH_VARARGS, "Adds a global to the JavaScript"},
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