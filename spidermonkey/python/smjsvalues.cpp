#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <format>
#include "smjspython.h"

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
   else if(args[i].isObject())
       {
       JS_ReportErrorUTF8(ctx, "Objects are not yet implemented");
       delete[] ret; return NULL;
       }
   else
       {
       JS::Value value = args[i];
       uint64_t data = *(uint64_t*)(void*)&value;
       data = data >> 47;
       std::string error = std::format("Unrecongnized JS type {:X}", data);
       JS_ReportErrorUTF8(ctx, error.c_str());
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

bool smjs_convertresult(JSContext* ctx, JS::CallArgs& args, PyObject* pobj)
{
 const char* tname = Py_TYPE(pobj)->tp_name;

 if(strcmp(tname, "NoneType") == 0)
    args.rval().setNull();
 else if(strcmp(tname, "str") == 0)
    {
    Py_ssize_t size = 0;
    const char* pstr = PyUnicode_AsUTF8AndSize(pobj, &size);
    JS::ConstUTF8CharsZ buf(pstr, size);
    JS::RootedString str(ctx, JS_NewStringCopyUTF8Z(ctx, buf));
    args.rval().setString(str);
    }
 else
    {
    std::string error = std::format("Unrecongnized python type {}", tname);
    JS_ReportErrorUTF8(ctx, error.c_str());
    return false;
    }
 return true;
}