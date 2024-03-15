#include <jsapi.h>
#include <js/Initialization.h>
#include <js/SourceText.h>
#include <js/CompilationAndEvaluation.h>

extern const JSClassOps DefaultGlobalClassOps;

static JSClass PythonGlobalClass = { "global", JSCLASS_GLOBAL_FLAGS, &JS::DefaultGlobalClassOps };

JSContext* init(void)
{
 if(!JS_Init())
    return NULL;

 return JS_NewContext(JS::DefaultHeapMaxBytes);
}

void finish(JSContext* ctx)
{
 JS_DestroyContext(ctx);
 JS_ShutDown();
}

bool evalJS(JSContext* ctx, const char* script)
{
 ctx = init();

 JS::InitSelfHostedCode(ctx);

 JS::RealmOptions* options = new JS::RealmOptions();
 JSObject* global = JS_NewGlobalObject(ctx, &PythonGlobalClass, nullptr, JS::FireOnNewGlobalHook, *options);

 JS::RootedObject* root = new JS::RootedObject(ctx, global);
 JSAutoRealm* ar = new JSAutoRealm(ctx, *root);

 JS::CompileOptions* opt = new JS::CompileOptions(ctx);
 opt->setFileAndLine("python", 1);

 JS::SourceText<mozilla::Utf8Unit>* source = new JS::SourceText<mozilla::Utf8Unit>();
 if(!source->init(ctx, script, strlen(script), JS::SourceOwnership::Borrowed))
    return false;

 JS::RootedValue* result =  new JS::RootedValue(ctx);
 if(!JS::Evaluate(ctx, *opt, *source, result))
    printf("fail\n");

  printf("%s\n", JS_EncodeStringToASCII(ctx, result->toString()).get());

 if(JS_IsExceptionPending(ctx))
   {
   printf("yep\n");
   }

 delete result;
 delete source;
 delete opt;
 delete ar;
 delete root;
 delete options;

 finish(ctx);

 return true;
}

int main(int argc, const char* argv[])
{
// JSContext* ctx = init();
 evalJS(NULL, "`hello world, it is `");
// finish(ctx);
}

