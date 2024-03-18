#include <iostream>
#include <jsapi.h>
#include <js/Initialization.h>
#include "smjs.h"

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
