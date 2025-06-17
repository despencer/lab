#include <stdio.h>
#include <stdint.h>

char msg[] = "_: Listen\n";

int main(void)
{
 uint32_t value = 0;

 printf(msg);
 (*msg) = '0' + value;
 printf(msg);
}