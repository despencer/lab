#ifndef __SPIDER_MONKEY_JAVASCRIPT__
#define __SPIDER_MONKEY_JAVASCRIPT__

#include <jsapi.h>
#include <js/Initialization.h>

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
};

#endif