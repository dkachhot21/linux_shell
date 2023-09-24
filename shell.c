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
    int i = 0;
    char *token = strtok(input, " ");
    char *args[50];
    while (token != NULL)
    {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    int pid=fork();
    if (pid<0)
    {
        exit(0);
    }
    else if (pid==0)
    {
        execvp(args[0],args);
    }
    
    return main;
}