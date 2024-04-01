#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include "smjsvalues.h"

jsconv_t* smjs_getconvertors(JSContext* ctx, JS::CallArgs& args)
{
// int len = 1;
// if(args.length() > 0) len = args.length();

 JS_ReportErrorUTF8(ctx, "Not found");

 return NULL;
}