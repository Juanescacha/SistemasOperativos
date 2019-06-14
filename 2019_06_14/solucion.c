#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int fibonacci(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  else return fibonacci(n - 1) + fibonacci(n - 2);
}

int guardarEntero(char *fn, int n) {
  FILE *fp;
  fp = fopen(fn, "w");
  fprintf(fp,"%d",n);
  fclose(fp);
  return 0;
}

int leerEntero(char *fn) {
  FILE *fp;
  int n;
  fp = fopen(fn,"r");
  fscanf(fp,"%d",&n);
  fclose(fp);
  return n;
}
