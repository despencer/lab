#include "smjs.h"

int main(int argc, const char* argv[])
{
 SMContext::init();
 SMContext* sm = SMContext::open();

 if(sm != NULL)
   {
     sm->evaluate("`hello world, it !`");
     sm->close();
     delete sm;
   }

 SMContext::shutdown();
}

