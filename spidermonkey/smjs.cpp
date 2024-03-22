#include <iostream>
#include "smjs.h"
#include <js/SourceText.h>
#include <js/CompilationAndEvaluation.h>
#include <js/Conversions.h>
#include <js/Object.h>

typedef void* pvoid_t;

SMFunction::SMFunction(jsfunc_t f, unsigned int n, jstype_t* a)
{
 function = f;
 numargs = n;
 argtypes = a;
}

bool SMFunction::call(JSContext* ctx, JS::CallArgs& args)
{
 pvoid_t* cargs = new pvoid_t[this->numargs+1];

 JS::RootedString message(ctx, args[0].toString());
 std::string ptr = JS_EncodeStringToUTF8(ctx, message).get();
 cargs[1] = &ptr;
 bool ret = this->function(cargs);
 delete[] cargs;
 return ret;
}

bool SMContext::init(void)
{
 if(!JS_Init())
     {
     std::cerr << "Can't initialize Spider Monkey\n";
     return false;
     }
 return true;
}

void SMContext::shutdown(void)
{
 JS_ShutDown();
}

static JSClass SMGlobalClass = { "global", JSCLASS_GLOBAL_FLAGS, &JS::DefaultGlobalClassOps };

SMContext* SMContext::open(void)
{
 JSContext* jscontext = JS_NewContext(JS::DefaultHeapMaxBytes);
 if(jscontext == NULL)
    {
    std::cerr << "Can't create JSContext\n";
    return NULL;
    }

 SMContext* context = new SMContext();
 context->context = jscontext;

 JS::InitSelfHostedCode(context->context);

 context->options = new JS::RealmOptions();
 context->global = JS_NewGlobalObject(context->context, &SMGlobalClass, nullptr, JS::FireOnNewGlobalHook, *context->options);
 context->root = new JS::RootedObject(context->context, context->global);
 context->realm = new JSAutoRealm(context->context, *context->root);
 return context;
}

void SMContext::close(void)
{
 delete this->realm;
 delete this->root;
 delete this->options;
 JS_DestroyContext(this->context);
 this->context = NULL;

 for(auto & ft : functions)
      delete ft;
 functions.clear();
}

bool SMContext::evaluate(const char* script)
{
 JS::CompileOptions* options = new JS::CompileOptions(this->context);
 options->setFileAndLine("script", 1);

 JS::SourceText<mozilla::Utf8Unit>* source = new JS::SourceText<mozilla::Utf8Unit>();
 bool ret = source->init(this->context, script, strlen(script), JS::SourceOwnership::Borrowed);

 JS::RootedValue* result =  new JS::RootedValue(this->context);

 if(ret)
    ret = JS::Evaluate(this->context, *options, *source, result);

 delete result;
 delete source;
 delete options;

 return ret;
}

void SMContext::reporterror(std::ostream& str)
{
 if(!JS_IsExceptionPending(this->context))
    return;

 JS::RootedValue* excpt = new JS::RootedValue(this->context);
 JS_GetPendingException(this->context, excpt);
 JS_ClearPendingException(this->context);

 {
  JS::RootedString message(this->context, JS::ToString(this->context, *excpt));
  if(!message)
      str << "Unable to convert the exception to a string\n";
  else
      str << JS_EncodeStringToUTF8(this->context, message).get() << "\n";
 }

 delete excpt;
}

bool cppnative(JSContext* ctx, unsigned argc, JS::Value* vp)
{
 JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
 JSObject* func = &args.callee();
 SMFunction* data = JS::GetMaybePtrFromReservedSlot<SMFunction>(func, 0);
 return data->call(ctx, args);
}

bool SMContext::addfunction(const char* name, jsfunc_t func, unsigned int numargs, jstype_t* argtypes)
{
 JSFunction* jsfunc = JS_DefineFunction(this->context, *this->root, name, cppnative, 0, 0);
 SMFunction* smf = new SMFunction(func, numargs, argtypes);
 this->functions.push_back(smf);
 JS::SetReservedSlot(JS_GetFunctionObject(jsfunc), 0, JS::PrivateValue(smf) );
 return true;
}