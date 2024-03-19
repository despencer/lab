#include <iostream>
#include "smjs.h"

static jstype_t print_args[] = {SMJS_NONE, SMJS_STRING};
void print(const void** args)
{
 const char* str = (const char*)args[1];
 std::cout << str << '\n';
}

int main(int argc, const char* argv[])
{
 SMContext::init();
 SMContext* sm = SMContext::open();
 sm->addfunction("print", &print, 1, print_args);

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

