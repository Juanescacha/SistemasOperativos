#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXCOM 1000 // numero maximo de letras sportado
#define MAXLIST 100 // numero maximo de comandos suportados
#define clear() printf("\033[H\033[J")

