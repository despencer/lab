#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include "smjsvalues.h"

PyObject* smjs_conv_string(JSContext* ctx, const JS::MutableHandleValue& value)
{
 JS::RootedString strvalue(ctx, value.toString());
 std::string str = JS_EncodeStringToUTF8(ctx, strvalue).get();
 return PyUnicode_FromString(str.c_str());
}

jsconv_t* smjs_getconvertors(JSContext* ctx, JS::CallArgs& args)
{
 unsigned int len = 1;
 if(args.length() > 0) len = args.length();

 jsconv_t* ret = new jsconv_t[len];

 for(unsigned int i=0; i<args.length(); i++)
   {
   if(args[i].isString())
       ret[i] = smjs_conv_string;
   else
       {
       JS_ReportErrorUTF8(ctx, "Unrecongnized JS type");
       delete[] ret;
       return NULL;
       }
   }

 return ret;
}

PyObject* smjs_convert(JSContext* ctx, JS::CallArgs& args, jsconv_t* converters)
{
 PyObject* list = PyList_New(0);
 for(unsigned int i=0; i<args.length(); i++)
   PyList_Append(list, converters[i](ctx, args[i]));
 return list;
}