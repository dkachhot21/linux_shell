#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define clear() printf("\033[H\033[J")

void start(){
    clear();
    char * username = getenv("USER");
    char * dir = getcwd(NULL,0);
    printf("\n%s@%s> ",username,dir);
}

int main(){
    start();
    char * input;
    scanf("%s",input);
    char * processed;
    int i;
    for ( i = 0; i < strlen(input); i++)
    {
        processed[i]=strtok(input," ");
    }
    printf("%s",processed);
    
    // int pid =fork();

    return 0;
}