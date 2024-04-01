#ifndef __SPIDER_MONKEY_PYTHON_VALUES__
#define __SPIDER_MONKEY_PYTHON_VALUES__

#include <jsapi.h>

typedef PyObject* (*jsconv_t)(JS::Value& value);

jsconv_t* smjs_getconvertors(JSContext* ctx, JS::CallArgs& args);

#endif
