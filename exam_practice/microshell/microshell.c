#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

// https://github.com/TalhaAksoy/microshellExam/blob/main/main.c
// https://github.com/shackbei/microshell-42/blob/main/microshell.c

/*not needed in exam, but necessary if you want to use this tester:
https://github.com/Glagan/42-exam-rank-04/blob/master/microshell/test.sh*/
#ifdef TEST_SH
# define TEST		1
#else
# define TEST		0
#endif

void    ft_putstr_fd2(char *str, char *arg)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(2, &str[i], 1);
        i++;
    }
    if (arg)
    {
        i = 0;
        while (arg[i])
        {
            write(2, &arg[i], 1);
            i++;
        }
    }
    write(2, "\n", 1);
}

void    ft_execute(char *argv[], int i, int tmp_fd, char *env[])
{
    argv[i] = NULL; //overwrite the ";" or "|" to NULL to use array as input to execve()
    dup2(tmp_fd, STDIN_FILENO); //create a child so we dont impact the parent process
    close(tmp_fd);
    execve(argv[0], argv, env);
    ft_putstr_fd2("error: cannot execute ", argv[0]);
    exit(1);
}

int main(int argc, char *argv[], char *env[])
{
    int fd[2];
    int tmp_fd;
    int i;

    i = 0;
    tmp_fd = dup(STDIN_FILENO);
    (void)argc;
    while (argv[i] && argv[i + 1])
    {
        argv = &argv[i + 1]; //the new argv start after the ; or |
        i = 0;
        // now we count until we have all the info to exec the next child:
        while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        if (i == 0 && argv[i] && (strcmp(argv[i], ";") == 0 || strcmp(argv[i], "|") == 0))
            continue ; // Skip empty commands
        if (strcmp(argv[0], "cd") == 0)
        {
            if (i != 2)
                ft_putstr_fd2("error: cd: bad arguments", NULL);
            else if (chdir(argv[1]) != 0)
                ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]);
        }
        else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0)) //exec in stdout
        {
            if (fork() == 0)
                ft_execute(argv, i, tmp_fd, env);
            else
            {
                close(tmp_fd);
                while (waitpid(-1, NULL, 0) > 0)
                    ;
                tmp_fd = dup(STDIN_FILENO);
            }
        }
        else if(i != 0 && strcmp(argv[i], "|") == 0) //pipe
        {
            pipe(fd);
            if (fork() == 0) // Child process
            {
                dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
                close(fd[0]); // Close unused read end
                close(fd[1]); // Close write end (already duplicated)
                ft_execute(argv, i, tmp_fd, env);
            }
            else // Parent process
            {
                close(fd[1]); // Close write end in parent
                close(tmp_fd); // Close old input
                tmp_fd = fd[0]; // Set new input to the read end of the pipe
            }
        }
    }
    close(tmp_fd);
    return (0);
}

// gcc ./microshell.c -Wall -Wextra -Werror -g3