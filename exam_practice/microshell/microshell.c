#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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
        while (argv[1] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
    }
}