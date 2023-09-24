#include<stdio.h>
#include<string.h>

int main(){
    char input[100];
    scanf("%[^\n]",input);
    char processed[10][50];
    int i=0;
    char * token = strtok(input," ");
    do
    {
        for (int j = 0; j < strlen(token); j++)
            processed[i][j]=token[j];
        token = strtok(NULL," ");
        i++;
    } while (token!=NULL);
    printf("%ld",strlen(processed[0]));
    for (int i = 0; i < 10; i++)
    {
        printf("%s\n",processed[i]);
    }
    return 0;
}