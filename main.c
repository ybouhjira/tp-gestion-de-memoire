#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memoire.h"

int main()
{
  Variable a = allouer("a", sizeof(short)),
           b = allouer("b", sizeof(char));
  short val = 123;
  char val2 = 'a';

  mem_afficher();

  memcpy((void*) mem.info + a.adrs, &val, sizeof(short));
  memcpy((void*) mem.info + b.adrs, &val2, sizeof(char));

  mem_afficher();

  printf("value = %d\n", *((short*) mem.info + a.adrs));
  printf("value = %c\n", *((char*) mem.info + b.adrs));

  return 0;
}
