#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
  * Este programa wait en C debe imprimir lo siguiente:
  * Soy el hijo y mi identificador es 34567
  * Soy el padre y mi indentificador es 34568 y el de mi hijo es 34567
 **/

int main (int argc , char** argv ) {
	pid_t pid;

	pid = fork();

	if(pid == 0){
		sleep(3);
		printf("Soy el hijo y mi identificador es %d \n" , (int) getpid());
	}

	else {
		int status;
		int pid2;
		wait(&status);
		printf("Soy el padre y mi identificador es %d y e de mi hijo %d \n" , (int) getpid() , pid );
		printf("Status %d \n",status);
		pid2 = wait(&status);
		printf("pid2 %d \n", pid2);
	}
}
