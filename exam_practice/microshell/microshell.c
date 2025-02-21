#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

// https://github.com/TalhaAksoy/microshellExam/blob/main/main.c
// https://github.com/shackbei/microshell-42/blob/main/microshell.c

int main(int argc, char *argv[], char *env[])
{
    int fd[2];
    int tmp_fd;
    int i;

    //void(argc);
    i = 0;
    tmp_fd = dup(STDIN_FILENO);
    while (argv[i] && argv[i + 1])
    {
        argv = &argv[i + 1]; //the new argv start after the ; or |
        i = 0;
        // now we count until we have all the info to exec the next child:
        while (argv[1] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        if (strcmp(argv[0], "cd" == 0))
        {
            printf("Caiu no CD\n");
        }
        else if (i != 0 && strcmp(argv[i], ";") == 0) //exec in stdout
        {
            printf("CAIU NO PONTO-VIRGULA\n");
        }
        else if (i != 0 && strcmp(argv[i], "|") == 0)
        {
            //pipe(fd);
            printf("CAIU NO PIPE\n");
        }
        close(tmp_fd);
        return (0);
    }
}