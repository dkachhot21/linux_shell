#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_INPUT_LENGTH 50
#define clear() printf("\033[H\033[J")

void start()
{
    clear();
    char *username = getenv("USER");
    char *dir = getcwd(NULL, 0);
    printf("\n%s@%s> ", username, dir);
}

int main()
{
    start();
    char input[MAX_INPUT_LENGTH];
    scanf("%[^\n]", input);
    char processed[10][MAX_INPUT_LENGTH];
    int i = 0;
    char *token = strtok(input, " ");
    const char* file=token;
    char *args[50];
    while (token != NULL)
    {
        token = strtok(NULL, " ");
        args[i] = token;
        i++;
    }
    args[i] = NULL;
    int pid =fork();
    execvp(file,args);
    
    return 0;
}