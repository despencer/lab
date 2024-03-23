#include <iostream>
#include "smjs.h"

static jstype_t print_args[] = {SMJS_NONE, SMJS_STRING};

bool print(void** args)
{
 std::string* str = (std::string*)args[1];
 std::cout << *str << '\n';
 return true;
}

void eval(void)
{
 SMContext* sm = SMContext::open();
 sm->addfunction("print", &print, 1, print_args);

 if(sm != NULL)
   {
     if(!sm->evaluate("a='Hello, world!'"))
       sm->reporterror(std::cerr);
     if(!sm->evaluate("print(a)"))
       sm->reporterror(std::cerr);
     sm->close();
     delete sm;
   }
}

int main(int argc, const char* argv[])
{
 SMContext::init();
 eval();
 eval();
 SMContext::shutdown();
}

