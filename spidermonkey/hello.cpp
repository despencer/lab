#include <iostream>
#include "smjs.h"

int main(int argc, const char* argv[])
{
 SMContext::init();
 SMContext* sm = SMContext::open();

 if(sm != NULL)
   {
//     sm->evaluate("`console.log('hello world, it !');`");
     if(!sm->evaluate("print('Hello, world!')"))
       sm->reporterror(std::cerr);
     sm->close();
     delete sm;
   }

 SMContext::shutdown();
}

