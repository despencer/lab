#ifndef __SPIDER_MONKEY_JAVASCRIPT__
#define __SPIDER_MONKEY_JAVASCRIPT__

#include <iostream>
#include <map>
#include <jsapi.h>
#include <js/Initialization.h>

typedef uint16_t jstype_t;
typedef bool (*jsfunc_t)(void**);
typedef bool (*jsfuncproxy_t)(std::string& name, JSContext* ctx, JS::CallArgs& args);

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

class SMProxyFunction
{
 public:
   std::string name;
   jsfuncproxy_t function;
 public:
   SMProxyFunction(const char* n, jsfuncproxy_t f) { name = n; function = f; };
   bool call(JSContext* ctx, JS::CallArgs& args) { return function(name, ctx, args); };
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
   std::map<JSFunction*, SMProxyFunction*> proxyfuncs;

 public:
   static bool init(void);
   static void shutdown(void);

   static SMContext* open(void);
   void close(void);
   bool evaluate(const char* script);
   std::string geterror(void);
   void reporterror(std::ostream& str);
   bool addfunction(const char* name, jsfunc_t func, unsigned int numargs, jstype_t* argtypes);
   bool addproxyfunction(const char* name, jsfuncproxy_t func);
};

#endif