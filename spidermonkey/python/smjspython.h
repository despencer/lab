#ifndef __SPIDER_MONKEY_PYTHON__
#define __SPIDER_MONKEY_PYTHON__

#include <jsapi.h>
#include <smjs.h>

typedef PyObject* (*jsconv_t)(JSContext* ctx, const JS::MutableHandleValue& value);

jsconv_t* smjs_getconvertors(JSContext* ctx, JS::CallArgs& args);
PyObject* smjs_convert(JSContext* ctx, JS::CallArgs& args, jsconv_t* converters);
bool smjs_convertresult(JSContext* ctx, JS::CallArgs& args, PyObject* pobj);

class SMPythonContext
{
public:
  SMContext* sm;
public:
  SMPythonContext(SMContext* _sm) { sm = _sm; }
  virtual ~SMPythonContext() {}
};

#endif
