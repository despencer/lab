#ifndef __SPIDER_MONKEY_JAVASCRIPT__
#define __SPIDER_MONKEY_JAVASCRIPT__

#include <iostream>
#include <jsapi.h>
#include <js/Initialization.h>

typedef uint16_t jstype_t;
typedef void (*jsfunc_t)(const void**);

#define SMJS_NONE     0
#define SMJS_STRING     1

class SMContext
{
 protected:
   JSContext* context;
   JS::RealmOptions* options;
   JSObject* global;
   JS::RootedObject* root;
   JSAutoRealm* realm;
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