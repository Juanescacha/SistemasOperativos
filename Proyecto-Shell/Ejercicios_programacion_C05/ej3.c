#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

/*
para resolver este ejercicio utilizare señales
*/

// Creamos el metodo para la señal que contiene el mensaje que dira el padre
void sig_handler(int a){

  printf("Adios\n");
  exit(0);

}

int main(int argc, char*argv[]){

  int pidPadre = getpid();
  int rc = fork();



   if (rc < 0) {
     fprintf(stderr, "fork failed\n");
     exit(1);
   }
   else if (rc == 0) {
     printf("hola\n");
     kill(pidPadre, SIGCONT); // utilizo el proceso kill para detener el proceso padre
   }
   else {
     signal(SIGCONT, sig_handler); // la señal SIGCONT permite continuar el proceso que habia detenido antes
     pause(); // esta funcion hace que se duerma el proceso padre hasta que reciba la señal que termina el proceso
  }
return 0;
}
