#include <iostream>
#include "smjs.h"
#include <js/SourceText.h>
#include <js/CompilationAndEvaluation.h>

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

 printf("%s\n", JS_EncodeStringToASCII(this->context, result->toString()).get());

 delete result;
 delete source;
 delete options;

 return ret;
}


