#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main (){

   printf("hello world (pid:%d)\n", (int) getpid());
   int rc = fork();
   int num = 10;

   if(rc < 0){
     fprintf(stderr, "fork failed\n");
     exit(1);
   }
   else if(rc == 0){
    printf("hola, yo soy el hijo (pid:%d)\n", (int) getpid());
    printf("el valor de la variable en hijo: %d\n", num);
    num = num * 10;
    printf("el hijo cambia el valor de la variable a: %d\n", num);
   }
   else{
    int rc_wait = wait(NULL);
    printf("hola, yo soy el padre de: %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    printf("el valor de la variable padre es: %d\n", num);
    num = num * 20;
    printf("el padre cambia el valor de la variable a: %d\n", num);
   }

return 0;
}
