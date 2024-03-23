#define PY_SSIZE_T_CLEAN
#include <python/Python.h>
#include <jsapi.h>
#include <js/Initialization.h>
#include <js/SourceText.h>
#include <js/CompilationAndEvaluation.h>

static JSClass PythonGlobalClass = { "global", JSCLASS_GLOBAL_FLAGS, &JS::DefaultGlobalClassOps };

bool evalJS(const char* script)
{
 if(!JS_Init())
    return false;

 JSContext* ctx = JS_NewContext(JS::DefaultHeapMaxBytes);
 JS::InitSelfHostedCode(ctx);

 JS::RealmOptions options;
 JSObject* global = JS_NewGlobalObject(ctx, &PythonGlobalClass, nullptr, JS::FireOnNewGlobalHook, options);

 JS::RootedObject root(ctx, global);
 JSAutoRealm ar(ctx, root);

 JS::CompileOptions opt(ctx);
 opt.setFileAndLine("python", 1);

 JS::SourceText<mozilla::Utf8Unit> source;
 if(!source.init(ctx, script, strlen(script), JS::SourceOwnership::Borrowed))
    return false;

 JS::RootedValue result(ctx);
 JS::Evaluate(ctx, opt, source, &result);

 if(JS_IsExceptionPending(ctx))
   {
   printf("yep");
   }

 JS_DestroyContext(ctx);
 JS_ShutDown();

 return true;
}

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

 if(!evalJS("print('Hello')"))
    return NULL;

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