#include <iostream>
#include "smjs.h"

static jstype_t print_args[] = {SMJS_NONE, SMJS_STRING};

bool print(void** args)
{
 std::string* str = (std::string*)args[1];
 std::cout << *str << '\n';
 return true;
}

void eval1(void)
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

void eval2(void)
{
 SMContext* sm1 = SMContext::open();
 sm1->addfunction("print", &print, 1, print_args);

 SMContext* sm2 = SMContext::open();
 sm2->addfunction("print", &print, 1, print_args);

 if(sm1 != NULL && sm2 != NULL)
   {
     if(!sm1->evaluate("a='Hello, world one!'"))
       sm1->reporterror(std::cerr);
     if(!sm2->evaluate("a='Hello, world second!'"))
       sm2->reporterror(std::cerr);
     if(!sm1->evaluate("print(a)"))
       sm1->reporterror(std::cerr);
     if(!sm2->evaluate("print(a)"))
       sm2->reporterror(std::cerr);
   }

 if(sm1 != NULL)
    { sm1->close(); delete sm1; }
 if(sm2 != NULL)
    { sm2->close(); delete sm2; }
}

int main(int argc, const char* argv[])
{
 SMContext::init();
 eval1();
 eval1();
 eval2();
 SMContext::shutdown();
}

