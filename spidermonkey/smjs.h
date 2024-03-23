#ifndef __SPIDER_MONKEY_JAVASCRIPT__
#define __SPIDER_MONKEY_JAVASCRIPT__

#include <iostream>
#include <map>
#include <jsapi.h>
#include <js/Initialization.h>

typedef uint16_t jstype_t;
typedef bool (*jsfunc_t)(void**);

#define SMJS_NONE     0
#define SMJS_STRING     1

class SMFunction
{
 public:
   jsfunc_t function;
   unsigned int numargs;
   jstype_t* argtypes;
 public:
   SMFunction(jsfunc_t f, unsigned int n, jstype_t* a);
   bool call(JSContext* ctx, JS::CallArgs& args);
};

class SMContext
{
 protected:
   JSContext* context;
   JS::RealmOptions* options;
   JSObject* global;
   JS::RootedObject* root;
   JSAutoRealm* realm;
 public:
   std::map<JSFunction*, SMFunction*> functions;

 public:
   static bool init(void);
   static void shutdown(void);

   static SMContext* open(void);
   void close(void);
   bool evaluate(const char* script);
   void reporterror(std::ostream& str);
   bool addfunction(const char* name, jsfunc_t func, unsigned int numargs, jstype_t* argtypes);
};

#endif