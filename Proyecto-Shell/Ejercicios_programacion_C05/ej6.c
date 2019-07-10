#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (){

   printf("hello world (pid:%d)\n", (int) getpid());
   int rc = fork();

   if(rc < 0){
     fprintf(stderr, "fork failed\n");
     exit(1);
   }
   else if(rc == 0){
     printf("hola., yo soy el hijo (pid:%d)\n", (int) getpid());
   }
   else{
     int st;
     int rc_wait =  waitpid(rc, &st, 0);
     printf("hola, yo soy el padre de: %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());

   }

return 0;
}
