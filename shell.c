#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")
#define size 1024

void parse(char *line, char **argv)
{
    while (*line != '\0')
    { /* if not the end of line ....... */
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0'; /* replace white spaces with \0    */
        *argv++ = line;     /* save the argument position     */
        while (*line != '\0' && *line != ' ' &&
               *line != '\t' && *line != '\n')
            line++; /* skip the argument until ...    */
    }
    *argv = '\0'; /* mark the end of argument list  */
}

void cd_case(char **argv)
{
    if (argv[1] == NULL)
    {
        const char *home = getenv("HOME");
        if (home != NULL)
        {
            if (chdir(home) == 0)
                return;
            else
                perror("cd");
        }
        else
            fprintf(stderr, "cd:Home environment variable is not set\n");
    }
    else
    {
        if (chdir(argv[1]) == 0)
            return;
        else
            perror("CD");
    }
}

void execute(char **argv)
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
    { /* fork a child process           */
        printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0)
    { /* for the child process:         */
        if (execvp(*argv, argv) < 0)
        { /* execute the command  */
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
    }
    else
    {                                /* for the parent:      */
        while (wait(&status) != pid) /* wait for completion  */
            ;
    }
}

void main(void)
{
    char line[size]; /* the input line                 */
    char *argv[64];  /* the command line argument      */
    clear();

    while (1)
    { /* repeat until done ....         */
        char *username = getenv("USER");
        char *dir = getcwd(NULL, 0);
        printf("\033[0;32m%s\033[0m:\033[0;34m%s\033[0m$ ", username, dir); /*   display a prompt             */
        if (fgets(line, size, stdin) == NULL)
        {
            perror("Input error");
            exit(1);
        } /*   read in the command line     */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') // remove new line from the end of input
        {
            line[len - 1] = '\0';
        }
        parse(line, argv); /*   parse the line   */
        if (argv[0] == NULL)
            continue;                     // Handle empty input
        if (strcmp(argv[0], "exit") == 0) /* is it an "exit"?     */
            exit(0);                      /*   exit if it is    */
        else if (strcmp(argv[0], "cd") == 0)
        {
            cd_case(argv);
        }
        else
            execute(argv); /* otherwise, execute the command */
        printf("\n");
        free(dir);
    }
    free(argv);
}