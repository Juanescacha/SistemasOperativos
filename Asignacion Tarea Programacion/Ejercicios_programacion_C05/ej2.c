#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main (){

   printf("hello world (pid:%d)\n", (int) getpid());
   // con la funcion open se abre el archivo y lo guardo en una variable llamada text
   int text =  open("file.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
   int rc = fork();

   if(rc < 0){
     fprintf(stderr, "fork failed\n");
     exit(1);
   }
   else if(rc == 0){
   printf("hola, yo soy el hijo (pid:%d)\n", (int) getpid());
   const char *  mensaje = "hola, soy el hijo\n"; // variable que contiene el mensaje que sera escrito por hijo
   write(text, mensaje, strlen(mensaje)); // escribir el mensaje en el archivo
   }
   else{
//    int rc_wait = wait(NULL);
    printf("hola, yo soy el padre de: %d (pid:%d)\n", rc,(int) getpid());
    const char * mensajep = "hola, yo soy el padre\n"; // mensaje que escribira el proceso padre
    write(text, mensajep, strlen(mensajep)); // escribir el mensaje
   }

return 0;
}
