#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#define ERROR_CD_ARGS "error: cd: bad arguments\n"
#define ERROR_CANNOT_CD "error: cd: cannor change directory to "
#define ERROR_EXEC "error: failed to execute "
#define ERROR_FATAL "error: fatal\n"

typedef struct s_data
{
    int     start;
    int     end;
    int     is_pipe;
    int     is_end;
} t_data;

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

int parse_comma(char **arg)
{
    int i = 0;

    while (arg[i])
    {
        if (strcmp(arg[i], ";") == 0 || strcmp(arg[i], "|") == 0)
        {
            if (strcmp(arg[i + 1], ";") == 0 || strcmp(arg[i + 1], "|") == 0)
            {
                write(2, ERROR_FATAL, ft_strlen(ERROR_FATAL));
                return (EXIT_FAILURE);
            }
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int get_arg_end(char **argv, t_data **data)
{
    int i = (*data)->start;

    printf("argv[i] = %s\n\n", argv[i]);
    while (argv[i] && strcmp(argv[i], ";"))
    {
        if (strcmp(argv[i], "|") == 0)
        {
            (*data)->is_pipe = 1;
            break ;
        }
        i++;
    }
    (*data)->end = i;
    if (!argv[i])
        (*data)->is_end = 1;
    argv[i] = NULL;
    return (i);
}

int exec_cmd(char **argv, t_data **data, int input_fd, char **env)
{   
    int status;
    int pipefd[2];
    pid_t pid;

    //printf("start: %s\nend: %s\nnext:%s\n\n", argv[(*data)->start], argv[(*data)->end], argv[(*data)->end + 1]);
    if (strcmp(argv[(*data)->start], "cd") == 0)
    {
        if ((*data)->end - (*data)->start != 2)
        {
            write(2, ERROR_CD_ARGS, ft_strlen(ERROR_CD_ARGS));
            return (EXIT_FAILURE);
        }
        else if (chdir(argv[(*data)->start + 1]))
        {
            write(2, ERROR_CANNOT_CD, ft_strlen(ERROR_CANNOT_CD));
            write(2, argv[(*data)->start + 1], ft_strlen(argv[(*data)->start + 1]));
            write(2, "\n", 1);
            return (EXIT_FAILURE);
        }
        return(EXIT_SUCCESS);
    }
    if ((*data)->is_pipe && pipe(pipefd) < 0)
    {
        write(2, ERROR_FATAL, ft_strlen(ERROR_FATAL));
        exit(EXIT_FAILURE);
    }
    pid = fork();
    printf("PID = %d\n", pid);
    if (pid < 0)
    {
        write(2, ERROR_FATAL, ft_strlen(ERROR_FATAL));
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if ((*data)->is_pipe)
        {
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
        }
        if (input_fd != -1) 
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        //printf("start: %s\nend: %s\n\n", argv[(*data)->start], argv[(*data)->end]);
        execve(argv[(*data)->start], &argv[(*data)->start], env);
        write(2, ERROR_EXEC, ft_strlen(ERROR_EXEC));
        write(2, argv[(*data)->start], ft_strlen(argv[(*data)->start]));
        write(2, "\n", 1);
        free(*data);
        exit(EXIT_FAILURE);
    }
    if ((*data)->is_pipe && !(*data)->is_end)
    {
        close(pipefd[1]);
        (*data)->start = (*data)->end + 1;
        //printf("VEIO DO EXEC\n");
        int res = get_arg_end(argv, data);
        if (res == EXIT_FAILURE)
            return (res);
        res = exec_cmd(argv, data, pipefd[0], env);
        close(pipefd[0]);
        //return (res);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (EXIT_FAILURE);
}

int main(int argc, char **argv, char **env)
{
    int i = 1;
    t_data  *data;
    (void)argc;

    while (argv[i] && argv[i + 1])
    {
        data = malloc(sizeof(t_data));
        data->start = i;
        data->end = 0;
        data->is_pipe = 0;
        data->is_end = 0;

        if (parse_comma(argv) == EXIT_FAILURE)
        {
            free(data);
            return (EXIT_FAILURE);
        }
        if (get_arg_end(argv, &data) == EXIT_FAILURE)
        {
            free(data);
            return (EXIT_FAILURE);
        }
        if (exec_cmd(argv, &data, -1, env) == EXIT_FAILURE)
        {
            free(data);
            return (EXIT_FAILURE);
        }
        if (data->is_end)
            i = data->end;
        else
            i = data->end + 1;
        free(data);
    }
    return (EXIT_SUCCESS);
}


// gcc ./microshell.c -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out /usr/bin/ls ";" /usr/bin/echo HELLO WORLD

// $>./a.out /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello world
// microshell

// ./a.out /bin/ls ";" cd folder ";" ";" echo hello
//ls ; cd folder ; ; echo hello

// ./a.out diff -U 3 test test.output "|" cat -e        ///com o 'cat -e' retorna 0 ||| sem o 'cat -e' retorna 1 se forem arquivos diferentes, 0 se forem iguais e 2 se der erro.

// ./a.out /bin/echo "Hello World" "|" /usr/bin/tee output.txt "|" /usr/bin/wc -w

// ./a.out seq 1 10 "|" /usr/bin/xargs -n1 echo "Number:"

// ./a.out /usr/bin/ls "|" /usr/bin/grep microshell ";" ";" /usr/bin/echo hello