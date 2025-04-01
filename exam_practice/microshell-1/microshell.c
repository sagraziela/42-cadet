#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#define STDIN   0
#define STDOUT   1
#define STDERR   2

#define TYPE_END   0
#define TYPE_BREAK   1
#define TYPE_PIPE   2

#define FD_OUT   0
#define FD_IN   1

typedef struct s_list
{
    char    **args;
    int     length;
    int     type;
    int     pipes[2];
    struct s_list   *prev;
    struct s_list   *next;
}   t_list;

void    clear_list(t_list **list)
{
    t_list  *tmp;
    int     i = 0;

    if (!*list)
        return ;
    while ((*list)->prev)
        *list = (*list)->prev;
    while (*list)
    {
        tmp = (*list)->next;
        if ((*list)->args)
        {
            i = 0;
            while ((*list)->args[i])
                free((*list)->args[i++]);
            free((*list)->args);
        }
        free(*list);
        *list = tmp;
    }
    return ;
}

int ft_stderr(char *msg, char *arg, t_list *cmds, int is_execerr)
{
    int i = 0;

    while (msg[i])
        write(STDERR, &msg[i++], 1);
    if (arg)
    {
        i = 0;
        while (arg[i])
            write(STDERR, &arg[i++], 1);
    }
    write(STDERR, "\n", 1);
    if (is_execerr)
    {
        clear_list(&cmds);
        exit(EXIT_FAILURE);
    }
    return (EXIT_FAILURE);
}

int fatal_error(void)
{
    write(STDERR, "error: fatal\n", 14);
    return (EXIT_FAILURE);
}

char    *ft_strdup(char *str)
{
    int i = 0;
    int len = 0;
    char    *dup;

    while (str[len])
        len++;
    dup = malloc(sizeof(char) * (len + 1));
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

int add_arg(t_list *cmds, char *arg)
{
    char    **new_args;
    int     i = 0;;

    new_args = (char **)malloc(sizeof(char *) * (cmds->length + 2));
    if (!new_args)
        return (fatal_error());
    if (cmds->args)
    {
        while (cmds->args[i])
        {
            new_args[i] = cmds->args[i];
            i++;
        }
        free(cmds->args);
    }
    new_args[i++] = ft_strdup(arg);
    new_args[i] = NULL;
    cmds->args = new_args;
    cmds->length++;
    return (EXIT_SUCCESS);
}

int push_list(t_list **cmds, char *arg)
{
    t_list  *new;

    new = malloc(sizeof(t_list));
    if (!new)
        return (fatal_error());
    new->args = NULL;
    new->length = 0;
    new->type = TYPE_END;
    new->prev = NULL;
    new->next = NULL;
    if (*cmds)
    {
        (*cmds)->next = new;
        new->prev = *cmds;
    }
    *cmds = new;
    return (add_arg(*cmds, arg));
}

int parse_args(t_list **cmds, char *arg)
{
    int is_break = 0;
    int is_pipe = 0;

    if (strcmp(arg, ";") == 0)
        is_break = 1;
    if (strcmp(arg, "|") == 0)
        is_pipe = 1;
    if ((is_break || is_pipe) && (!*cmds || (*cmds)->type > TYPE_END))
        return (fatal_error());
    else if (!is_break && !is_pipe && (!*cmds || (*cmds)->type > TYPE_END))
        return (push_list(cmds, arg));
    else if (is_break)
        (*cmds)->type = TYPE_BREAK;
    else if (is_pipe)
        (*cmds)->type = TYPE_PIPE;
    else
        return (add_arg(*cmds, arg));
    return (EXIT_SUCCESS);
}

char *get_cmd(char *str)
{
    int len = 0;
    int i = 0;
    char    *path = "/usr/bin/";
    char    *cmd;

    if (!strncmp(str, "/usr/", 5) || !strncmp(str, "/bin/", 5))
        return (ft_strdup(str));
    while (str[len])
        len++;
    cmd = malloc(sizeof(char) * (len + 10));
    while (path[i])
    {
        cmd[i] = path[i];
        i++;
    }
    len = 0;
    while (str[len])
        cmd[i++] = str[len++];
    return (cmd);
}

int exec_cmd(t_list *cmd, char **env)
{
    pid_t   pid;
    int     res = EXIT_FAILURE;
    int     status;
    int     pipe_open = 0;
    char    *full_cmd;

    if (cmd->type == TYPE_PIPE || (cmd->prev && cmd->prev->type == TYPE_PIPE))
    {
        pipe_open = 1;
        if (pipe(cmd->pipes))
            return (fatal_error());
    }
    pid = fork();
    if (pid < 0)
        return (res);
    else if (pid == 0)
    {
        if (cmd->type == TYPE_PIPE && dup2(cmd->pipes[FD_IN], STDOUT) < 0)
            return (fatal_error());
        if (cmd->prev && cmd->prev->type == TYPE_PIPE
            && dup2(cmd->prev->pipes[FD_OUT], STDIN) < 0)
            return (fatal_error());
        full_cmd = get_cmd(cmd->args[0]);
        res = execve(full_cmd, cmd->args, env);
        free(full_cmd);
        ft_stderr("error: failed to execute ", cmd->args[0], cmd, 1);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (pipe_open)
        {
            close(cmd->pipes[FD_IN]);
            if (!cmd->next || cmd->type == TYPE_BREAK)
                close(cmd->pipes[FD_OUT]);
            if (cmd->prev && cmd->prev->type == TYPE_PIPE)
                close(cmd->prev->pipes[FD_OUT]);
        }
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        return (EXIT_FAILURE);
    }
    return (res);
}

int exec_cmds(t_list **cmds, char **env)
{
    t_list  *tmp;
    int     res = EXIT_FAILURE;

    if ((*cmds)->prev)
    {
        while ((*cmds)->prev)
            *cmds = (*cmds)->prev;
    }
    tmp = *cmds;
    while (*cmds)
    {
        if (strcmp((*cmds)->args[0], "cd") == 0)
        {
            if ((*cmds)->length != 2)
                return (ft_stderr("error: cd: bad arguments", NULL, NULL, 0));
            if (chdir((*cmds)->args[1]))
                return (ft_stderr("error: cd: cannot change to directory ", (*cmds)->args[1], NULL, 0));
        }
        else
            res = exec_cmd(*cmds, env);
        *cmds = (*cmds)->next;
    }
    *cmds = tmp;
    return (res);
}

int main(int argc, char **argv, char **env)
{
    t_list  *cmds = NULL;
    int     i = 1;
    int     res = EXIT_SUCCESS;
    int     res_parse = EXIT_SUCCESS;

    if (argc < 2)
        return (res);
    while (argv[i] && res_parse == EXIT_SUCCESS)
        res_parse = parse_args(&cmds, argv[i++]);
    if (res_parse == EXIT_SUCCESS && cmds)
        res = exec_cmds(&cmds, env);
    (void)env;
    clear_list(&cmds);
    return (res);
}




// gcc ./microshell.c -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out ls ";" echo HELLO WORLD

// $>./a.out /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello world
// microshell

// ./a.out diff -U 3 test test.output "|" cat -e        ///com o 'cat -e' retorna 0 ||| sem o 'cat -e' retorna 1 se forem arquivos diferentes, 0 se forem iguais e 2 se der erro.

// ./a.out /bin/echo "Hello World" "|" /usr/bin/tee output.txt "|" /usr/bin/wc -w

// ./a.out seq 1 10 "|" /usr/bin/xargs -n1 echo "Number:"

// ./a.out ls "|" grep microshell ";" ";" echo hello
