#include "solucion.h"
#include <stdio.h>

int main(int argc, char** argv) {
  int x = 20;

  printf("fibonacci(%d) = ",x);
  x = fibonacci(x);
  printf("%d\n",x);
  guardarEntero("archivo",x);

  return 0;
}
