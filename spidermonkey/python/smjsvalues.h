#ifndef __SPIDER_MONKEY_PYTHON_VALUES__
#define __SPIDER_MONKEY_PYTHON_VALUES__

#include <jsapi.h>

typedef PyObject* (*jsconv_t)(JSContext* ctx, const JS::MutableHandleValue& value);

jsconv_t* smjs_getconvertors(JSContext* ctx, JS::CallArgs& args);
PyObject* smjs_convert(JSContext* ctx, JS::CallArgs& args, jsconv_t* converters);

#endif
