#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

int main (){

   printf("hello world (pid:%d)\n", (int) getpid());
   int rc = fork();

   if(rc < 0){
     fprintf(stderr, "fork failed\n");
     exit(1);
   }
   else if(rc == 0){
     // para usar el wait en el hijo
     int rc_waith = wait (NULL);
     printf("hola, yo soy el hijo (rc_wait:%d)  (pid:%d)\n", rc_waith, (int) getpid());

     // hijo sin el wait
     //printf("hola., yo soy el hijo (pid:%d)\n", (int) getpid());
   }
   else{
     //para usar el wait en el padre
     //int rc_wait = wait(NULL);
     //printf("hola, yo soy el padre de: %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());

     //padre sin el wait
     printf("hola, yo soy el padre de: %d  (pid:%d)\n", rc, (int) getpid());
   }

return 0;
}
