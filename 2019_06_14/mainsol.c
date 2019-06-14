#include "solucion.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {

	int x = 20;
	pid_t pid;
	pid = fork();

	if(pid == 0){
		//Codigo Hijo
		x = fibonacci(x);
		guardarEntero("archivo",x);

	} else {
		//Codig Padre
		int estado;
		int resultado;
		wait(&estado);
		resultado = leerEntero("archivo");
		printf("El Fibonacci de %d es %d \n" , x , resultado*100 );
	}

	return 0;
}
