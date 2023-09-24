#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    int pid=fork();
    char* args[]={"update",NULL};
    if (pid<0)
    {
        exit(0);
    }
    else if (pid==0)
    {
        execvp("apt",args);
    }
    
    return 0;
}