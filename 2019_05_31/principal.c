#include <stdio.h>
#include "entero.h"

int main(int argc, char** argv) {
  entero a,b;

  a = 5;
  b = 6;
  printf("la suma de %d + %d es %d\n",a,b,suma(a,b));
}
