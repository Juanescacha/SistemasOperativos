#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

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
	printf(" \n shell=%s" , cwd);

}

// Recibir Entrada

int recEntrada (char* str) {

	char* buf;
	buf = readline("$ ");

	if (strlen(buf) != 0) {
		add_history(buf);
		strcpy(str, buf);
		return 0;
	} else {
		return 1;
	}

}

void execArgs(char** parsed) {

	//Hacemos un Fork Hijo
	pid_t pid = fork();

	if (pid == -1) {
		printf(" \n Fallo crear Fork Hijo");
		return;
	} else if ( pid == 0 ) {
		if ( execvp(parsed[0], parsed) < 0) {
			printf(" \n No se puedo ejecutar el comando");
		}
		exit(0);
	} else {
		// Esperar al Hijo que Termine
		wait(NULL);
		return;
	}

}

void execArgsPiped(char** parsed , char** parsedpipe) {

	int pipefd[2];
	pid_t p1, p2;

	if(pipe(pipefd) < 0) {
		printf(" \n Pipe no pudo ser inicializado");
		return;
	}
	p1 = fork();
	if (p1 < 0) {
		printf(" \n No se pudo hacer el Fork");
		return;
	}
	if (p1 == 0) {
		//Ejecucion del hijo 1
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parsed[0], parsed) < 0) {
			printf(" \n No se pudo Ejecutar el comando 1");
			exit(0);
		}
	} else {
		// Ejecucion del Padre
		p2 = fork();

		if (p2 < 0) {
			printf(" \n No se pudo hacer el Fork");
			return;
		}

		// Hijo 2 Ejecutandose
		if (p2 ==0) {
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if ( execvp(parsedpipe[0], parsedpipe) < 0) {
				printf(" \n No se pudo ejecutar el comando 2");
				exit(0);
			}
		} else {
			// Padre ejecutandose , esperando por los hijos
			wait(NULL);
			wait(NULL);
		}
	}
}

void abrirAyuda() {

	puts("\n *** Bienvenidos a la Ayuda de la Shell ***"
	"\n Lista de Comandos Soportados:"
	"\n >cd"
	"\n >ls"
	"\n >quit"
	"\n >hola"
	"\n >clr"
	"\n >pause"
	"\n >dir"
	"\n >environ"
	"\n >echo");
	return;

}

int ownCmdHandler(char **parsed) {

	int NoOfOwnCmds = 8, i, switchOwnArg = 0;
	char* ListOfOwnCmds [NoOfOwnCmds];
	char* username;

	ListOfOwnCmds[0] = "quit";
	ListOfOwnCmds[1] = "cd";
	ListOfOwnCmds[2] = "help";
	ListOfOwnCmds[3] = "hola";
	ListOfOwnCmds[4] = "clr";
	ListOfOwnCmds[5] = "pause";
	ListOfOwnCmds[6] = "dir";
	ListOfOwnCmds[7] = "environ";

	for (i = 0; i < NoOfOwnCmds; i++) {
		if(strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
			switchOwnArg = i + 1;
			break;
		}
	}

	switch (switchOwnArg) {
	case 1:
		printf("\n Adios \n");
		exit(0);
	case 2:
		if(parsed[1] == NULL) system("pwd");
		else {
			char buffer[1000];
			snprintf(buffer, sizeof(buffer), "cd %s", parsed[1]);
			system(buffer);
			snprintf(buffer, sizeof(buffer), "echo $? > /dev/null");
			if(system(buffer) == 0) {

				chdir(parsed[1]);
			}
		}
		return 1;
	case 3:
		abrirAyuda();
		return 1;
	case 4:
		username = getenv("USER");
		printf("\n Hola %s , usa el comando help para saber mas comandos.. \n" , username);
		return 1;
	case 5:
		clear();
		return 1;
	case 6:
		printf("\n Presiona Enter para continuar... \n");
		while (1) {
			char ch = getchar();
			if (ch == '\n') return 1;
		}
	case 7:
		if(parsed[1] == NULL) system("ls");
		else {
			chdir(parsed[1]);
			system("ls");
		}
		return 1;
	case 8:
		system("printenv");
		return 1;
	default:
		break;
	}

	return 0;

}

int parsePipe(char* str , char** strpiped) {
	for ( int i = 0 ; i < 2;  i++ ) {
		strpiped[i] = strsep(&str , "|");
		if (strpiped[i] == NULL) break;
	}

	if (strpiped[1] == NULL) return 0;
	else return 1;
}

void parseSpace(char* str , char** parsed) {

	for ( int i = 0; i < MAXARGS; i++) {
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL) break;
		if (strlen(parsed[i]) == 0) i--;
	}

}

int processString(char* str, char** parsed, char** parsedpipe) {

	char* strpiped[2];
	int piped = 0;

	piped = parsePipe(str, strpiped);

	if (piped) {
		parseSpace(strpiped[0], parsed);
		parseSpace(strpiped[1], parsedpipe);
	} else {
		parseSpace(str, parsed);
	}

	if (ownCmdHandler(parsed))
		return 0;
	else
		return 1 + piped;
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

	// Leer Entrada Usuario
	if (recEntrada(inputString)) continue;

	execFlag = processString(inputString, parsedArgs, parsedArgsPiped);
	// exexcFlag retorna 0, si no hay comando o si es uno integrado
	// retorna 1, si es un comando simple
	// retorna 2 si es un comando incluyendo un pipe

	if (execFlag == 1) execArgs(parsedArgs);
	if (execFlag == 2) execArgsPiped(parsedArgs, parsedArgsPiped);

	}

	return 0;
}
