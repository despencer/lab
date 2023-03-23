#include <stdio.h>

#define A "a\n"
#define B "b\n"

#undef A
#define A "aa\n"

int main(void)
{
 printf(A);
 printf(B);
}