#include <stdint.h>

int tswitch(int c)
{
 switch(c)
 {
  case 0:
   __attribute__ ((fallthrough));
  case 1:
    return 0;
 }
 return 2;
}

int main()
{
 return tswitch(1);
}