#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#define ERROR_CD_ARGS "error: cd: bad args\n"
#define ERROR_CANNOT_CD "error: cd: cannot change dir to "
#define ERROR_EXEC "error: cannot exec "
#define ERROR_FATAL "error: fatal\n"

typedef struct s_data
{
    int start;
    int end;
    int is_pipe;
    int is_end;
    int fds[2];
} t_data;

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

int parse(char **arg)
{
    int i = 1;

    while (arg[i])
    {
        if (strcmp(arg[i], ";") == 0)
        {
            if (i == 1 || !arg[i + 1] || (arg[i + 1] && strcmp(arg[i + 1], ";") == 0))
            {
                write(2, ERROR_FATAL, ft_strlen(ERROR_FATAL));
                return (EXIT_FAILURE);
            }
        }
        if (strcmp(arg[i], "|") == 0 && i == 1)
        {
            if (i == 1 || !arg[i + 1])
            {
                write(2, ERROR_FATAL, ft_strlen(ERROR_FATAL));
                return (EXIT_FAILURE);
            }
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int get_arg_end(char **arg, t_data **data)
{
    int i = (*data)->start;

    //printf("%s\n\n", arg[i]);
    while (arg[i] && strcmp(arg[i], ";"))
    {
        if (strcmp(arg[i], "|") == 0)
        {
            (*data)->is_pipe = 1;
            break ;
        }
        i++;
    }
    (*data)->end = i;
    if (arg[i] == NULL)
        (*data)->is_end = 1;
    return (EXIT_SUCCESS);
}

int handle_cd(char **argv, t_data **data, int i)
{
    if ((*data)->end - (*data)->start != 2)
    {
        write(2, ERROR_CD_ARGS, ft_strlen(ERROR_CD_ARGS));
        return (EXIT_FAILURE);
    }
    else if (chdir(argv[i + 1]))
    {
        write(2, ERROR_CANNOT_CD, ft_strlen(ERROR_CANNOT_CD));
        write(2, argv[i + 1], ft_strlen(argv[i + 1]));
        write(2, "\n", 1);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int exec_cmds(char **argv, t_data **data, int input_fd, char **env)
{
    pid_t   pid;
    int     status;
    int     res = EXIT_SUCCESS;
    int     i = (*data)->start;

    argv[(*data)->end] = NULL;
    if (strcmp(argv[i], "cd") == 0)
    {
        return (handle_cd(argv, data, i));
    }
    if ((*data)->is_pipe && pipe((*data)->fds) < 0)
    {
        return (EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0)
        return (EXIT_FAILURE);
    if (pid == 0)
    {
        if ((*data)->is_pipe)
        {
            dup2((*data)->fds[1], STDOUT_FILENO);
            close((*data)->fds[0]);
            close((*data)->fds[1]);
        }
        if (input_fd != -1)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        res = execve(argv[i], &argv[i], env);
        write(2, ERROR_EXEC, ft_strlen(ERROR_EXEC));
        write(2, argv[i], ft_strlen(argv[i]));
        write(2, "\n", 1);
        free(*data);
        exit (res);
    }
    waitpid(pid, &status, 0);
    if ((*data)->is_pipe)
    {
        close((*data)->fds[1]);
        // input_fd = fds[0];
    }
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (EXIT_FAILURE);
}

int main(int argc, char **argv, char **env)
{
    t_data  *data;
    int     i = 1;
    int     res = EXIT_SUCCESS;
    int     parse_res = EXIT_SUCCESS;

    if (argc < 2)
        return (EXIT_SUCCESS);
    parse_res = parse(argv);
    if (parse_res == EXIT_FAILURE)
        return (EXIT_FAILURE);
    data = malloc(sizeof(t_data));
    if (!data)
    {
        write(2, ERROR_FATAL, ft_strlen(ERROR_FATAL));
        return (EXIT_FAILURE);
    }
    data->fds[0] = -1;
    data->fds[1] = -1;
    while (argv[i])
    {
        data->start = i;
        data->is_end = 0;
        data->is_pipe = 0;
        get_arg_end(argv, &data);
        res = exec_cmds(argv, &data, data->fds[0], env);
        if (res == EXIT_FAILURE || data->is_end)
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

// ./a.out /bin/echo "Hello World" | /usr/bin/tr ' ' '_' | /usr/bin/wc -c

// ./a.out /bin/echo Hello World "|" /usr/bin/tee output.txt "|" /usr/bin/wc -w
// echo "Hello World" | tee output.txt | wc -w

// ./a.out /bin/seq 1 10 "|" /usr/bin/xargs -n1 echo "Number:"

// ./a.out /usr/bin/ls "|" /usr/bin/grep microshell ";" ";" /usr/bin/echo hello
