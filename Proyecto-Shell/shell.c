#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXLETTERS 1000 // numero maximo de letras sportado
#define MAXARGS 100 // numero maximo de comandos suportados
#define clear() printf(" \033[H\033[J ")

// Inicio de Shell

void init_shell() {

	clear();
	printf(" \n\n\n Bienvenidos a nuestra Shell ");
	char* username = getenv("USER");
	printf(" \n\n\n  Usuario : @%s ", username);
	printf(" \n ");
	sleep(1);
	clear();

}

// Mostrar Interfaz

void printDir() {

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf(" \n shell=%s/myshell " , cwd);

}


int main() {

	char inputString[MAXLETTERS] , *parsedArgs[MAXARGS];
	char*parsedArgsPiped[MAXARGS];
	int execFlag = 0;

	// Mensaje de Bienvenida Shell
	init_shell();

	while(1) {

	// Mostrar Interfaz
	printDir();


	}

	return 0;
}
