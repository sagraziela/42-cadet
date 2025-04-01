#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#define ERR_CD_ARGS "error: cd: bad arguments"
#define ERR_CD_FAILED "error: cd: cannot change directory to "
#define ERR_EXEC "error: cannot execute "
#define ERR_FATAL "error: fatal"

typedef struct s_data
{
    int start;
    int end;
    int is_pipe;
    int is_end;
    int prev_fd;
}   t_data;


int show_error(char *msg, char *arg)
{
    int i = 0;

    while (msg[i])
    {
        write(2, &msg[i], 1);
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
    return (EXIT_FAILURE);
}

int parse(char **argv)
{
    int i = 1;

    while (argv[i])
    {
        if (strcmp(argv[i], ";") == 0)
        {
            if (strcmp(argv[i + 1], ";") == 0 || strcmp(argv[i + 1], "|") == 0)
                return (show_error(ERR_FATAL, NULL));
        }
        if (strcmp(argv[i], "|") == 0)
        {
            if (strcmp(argv[i + 1], ";") == 0 || strcmp(argv[i + 1], "|") == 0)
                return (show_error(ERR_FATAL, NULL));
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int get_cmd_end(t_data **data, char **argv, int i)
{
    while (argv[i] && strcmp(argv[i], ";") != 0)
    {
        if (strcmp(argv[i], "|") == 0)
        {
            (*data)->is_pipe = 1;
            break ;
        }
        i++;
    }
    (*data)->end = i;
    if (argv[i] == NULL)
        (*data)->is_end = 1;
    return (i);
}

int handle_cd(t_data **data, char **argv)
{
    int i = (*data)->start;

    if ((*data)->end - i != 2)
        return (show_error(ERR_CD_ARGS, NULL));
    if (chdir(argv[i + 1]))
        return (show_error(ERR_CD_FAILED, argv[i + 1]));
    return (EXIT_SUCCESS);
}

int exec_cmd(t_data **data, char **argv, char **env)
{
    pid_t   pid;
    int     status;
    int     i = (*data)->start;
    int     res = EXIT_FAILURE;
    int     fd[2];

    argv[(*data)->end] = NULL;
    if (strcmp(argv[i], "cd") == 0)
        return (handle_cd(data, argv));
    if ((*data)->is_pipe && pipe(fd) < 0)
        return (EXIT_FAILURE);
    pid = fork();
    if (pid < 0)
        return (show_error(ERR_FATAL, NULL));
    if (pid == 0)
    {
        if ((*data)->prev_fd != -1)
        {
            dup2((*data)->prev_fd, STDIN_FILENO);
            close((*data)->prev_fd);
        }
        if ((*data)->is_pipe)
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
        }
        res = execve(argv[i], &argv[i], env);
        show_error(ERR_EXEC, argv[i]);
        free(*data);
        exit(res);
    }
    waitpid(pid, &status, 0);
    if ((*data)->prev_fd != -1)
        close ((*data)->prev_fd);
    if ((*data)->is_pipe)
    {
        close(fd[1]);
        (*data)->prev_fd = fd[0];
    }
    else
        (*data)->prev_fd = -1;
    
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (res);
}


int main(int argc, char **argv, char **env)
{
    t_data  *data;
    int     i = 1;
    int     res = EXIT_SUCCESS;

    if (argc < 2)
        return (EXIT_SUCCESS);
    if (parse(argv) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    data = malloc(sizeof(t_data));
    data->prev_fd = -1;
    data->is_end = 0;
    data->is_pipe = 0;
    while (argv[i])
    {
        // if (!data->is_pipe && data->prev_fd != -1)
        //     data->prev_fd = -1;
        data->start = i;
        data->is_pipe = 0;
        get_cmd_end(&data, argv, i);
        res = exec_cmd(&data, argv, env);
        if (data->is_end)
            break ;
        i = data->end + 1;
    }
    free(data);
    return (res);
}



// gcc ./microshell.c -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out /usr/bin/ls ";" /usr/bin/echo HELLO WORLD

// valgrind --leak-check=full --show-leak-kinds=all ./a.out /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello world
// microshell

// ./a.out /bin/ls ";" cd folder ";" ";" /bin/echo hello
//ls ; cd folder ; ; echo hello

// ./a.out /bin/diff -U 3 test test.output "|" /bin/cat -e        ///com o 'cat -e' retorna 0 ||| sem o 'cat -e' retorna 1 se forem arquivos diferentes, 0 se forem iguais e 2 se der erro.

// ./a.out /bin/echo Hello World "|" /usr/bin/tr ' ' '_' | /usr/bin/wc -c

// ./a.out /bin/echo Hello World "|" /usr/bin/tee output.txt "|" /usr/bin/wc -w
// echo "Hello World" | tee output.txt | wc -w

// ./a.out /bin/seq 1 10 "|" /usr/bin/xargs -n1 echo "Number:"

// ./a.out /usr/bin/ls "|" /usr/bin/grep microshell ";" ";" /usr/bin/echo hello