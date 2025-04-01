#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#define STDIN   0
#define STDOUT  1
#define STDERR  2

#define TYPE_END    0
#define TYPE_BREAK  1
#define TYPE_PIPE   2

#define FD_OUT  0
#define FD_IN   0

typedef struct s_list
{
    char            **args;
    int             length;
    int             type;
    int             pipes[2];
    struct s_list   *prev;
    struct s_list   *next;
}   t_list;



void    clear_list(t_list **list)
{
    t_list  *tmp;
    int     i;

    if (!*list)
        return ;
    if ((*list)->prev)
    {
        while ((*list)->prev)
            *list = (*list)->prev;
    }
    while (*list)
    {
        tmp = (*list)->next;
        i = 0;
        if ((*list)->args)
        {
            while ((*list)->args[i])
                free((*list)->args[i++]);
            free((*list)->args);
        }
        free(*list);
        *list = tmp;
    }
    return ;
}

int fatal_error(t_list *cmds)
{
    write(STDERR, "error: fatal\n", 14);
    if (cmds)
        clear_list(&cmds);
    return (EXIT_FAILURE);
}

int ft_strerr(t_list *cmds, char *msg, char *arg, int is_exec)
{
    int i;

    i = 0;
    while (msg[i])
        write(STDERR, &msg[i++], 1);
    if (arg)
    {
        i = 0;
        while (arg[i])
            write(STDERR, &arg[i++], 1);
    }
    write(STDERR, "\n", 1);
    if (is_exec)
    {
        clear_list(&cmds);
        exit(EXIT_FAILURE);
    }
    return (EXIT_FAILURE);
}

char    *ft_strdup(char *str)
{
    char    *dup;
    int     len;
    int     i;

    i = 0;
    len = 0;
    while (str[len])
        len++;
    dup = malloc(sizeof(char) * len + 1);
    if (!dup)
        return (NULL);
    while (i < len)
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

int add_arg(t_list *cmd, char *arg)
{
    char    **new_args;
    int     i;

    new_args = (char **)malloc(sizeof(char *) * (cmd->length + 2));
    if (!new_args)
        return (fatal_error(cmd));
    i = 0;
    while (i < cmd->length)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    free(cmd->args);
    new_args[i++] = ft_strdup(arg); //não trata erro se retornar NULL
    new_args[i] = NULL;
    cmd->args = new_args;
    cmd->length++;
    return (EXIT_SUCCESS);
}

int list_push(t_list **cmds, char *arg)
{
    t_list  *new;

    new = malloc(sizeof(t_list));
    if (!new)
        return (fatal_error(*cmds));
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
    int is_break;
    int is_pipe;

    is_break = 0;
    is_pipe = 0;
    if (strcmp(arg, ";") == 0)
        is_break = 1;
    if (strcmp(arg, "|") == 0)
        is_pipe = 1;
    if ((is_break || is_pipe) && (!*cmds || (*cmds)->type > TYPE_END))
        return (fatal_error(*cmds));
    else if (!is_break && !is_pipe && (!*cmds || (*cmds)->type > TYPE_END))
        return (list_push(cmds, arg));
    else if (is_break)
        (*cmds)->type = TYPE_BREAK;
    else if (is_pipe)
        (*cmds)->type = TYPE_PIPE;
    else
        return (add_arg(*cmds, arg));
    return (EXIT_SUCCESS);
}

char    *get_cmd(char *cmd)
{
    char    *full_cmd;
    char    *path;
    int     i;
    int     len;

    if (strncmp(cmd, "/usr", 4) == 0 || (strncmp(cmd, "/bin", 4) == 0))
        return (cmd);
    path = "/usr/bin/";
    i = 0;
    len = 0;
    while (cmd[len])
        len++;
    full_cmd = malloc(sizeof(char) * len + 10);
    while (path[i])
    {
        full_cmd[i] = path[i];
        i++;
    }
    len = 0;
    while (cmd[len])
        full_cmd[i++] = cmd[len++];
    full_cmd[i] = '\0';
    return (full_cmd);
}

int exec_cmd(t_list *cmd, char **env)
{
    pid_t   pid;
    int     status;
    int     ret;
    int     pipe_open;
    char    *full_cmd;

    ret = EXIT_SUCCESS;
    pipe_open = 0;
    if (cmd->type == TYPE_PIPE || (cmd->prev && cmd->prev->type == TYPE_PIPE))
    {
        pipe_open = 1;
        if (pipe(cmd->pipes) != 0)
            return (fatal_error(cmd));
    }
    pid = fork();
    if (pid < 0)
        return (fatal_error(cmd));
    else if (pid == 0)
    {
        if (cmd->type == TYPE_PIPE && dup2(cmd->pipes[FD_IN], STDOUT) < 0)
            return (fatal_error(cmd));
        if (cmd->prev && cmd->prev->type == TYPE_PIPE
            && dup2(cmd->pipes[FD_OUT], STDIN) < 0)
            return (fatal_error(cmd));
        full_cmd = get_cmd(cmd->args[0]);
        if (!full_cmd)
            return (fatal_error(cmd));
        ret = execve(full_cmd, cmd->args, env);
        return(ft_strerr(cmd, "error: cannot execute ", cmd->args[0], 1));
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (pipe_open)
        {
            close (cmd->pipes[FD_IN]);
            if (!cmd->next || cmd->type == TYPE_BREAK)
                close(cmd->pipes[FD_OUT]);
            if (cmd->prev && cmd->prev->type == TYPE_PIPE)
                close(cmd->prev->pipes[FD_OUT]);
        }
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        return (EXIT_FAILURE);
    }
    return (ret);
}

int exec_cmds(t_list **cmds, char **env)
{
    t_list  *tmp;
    int     ret;

    ret = EXIT_SUCCESS;
    while ((*cmds)->prev)
        *cmds = (*cmds)->prev;
    tmp = *cmds;
    while (*cmds)
    {
        if (strcmp((*cmds)->args[0], "cd") == 0)
        {
            if ((*cmds)->length != 2)
                return (ft_strerr(*cmds, "error: cd: bad arguments", NULL, 0));
            else if (chdir((*cmds)->args[1]))
                return (ft_strerr(*cmds, "error: cd: cannot change directory to ", (*cmds)->args[1], 0));
        }
        else
            ret = exec_cmd(*cmds, env);
        *cmds = (*cmds)->next;
    }
    *cmds = tmp;
    return (ret);
}

int main(int argc, char **argv, char **env)
{
    t_list  *cmds;
    int     i;
    int     ret;

    ret = EXIT_SUCCESS;
    if (argc < 2)
        return (ret);
    cmds = NULL;
    i = 1;
    while (argv[i])
        ret = parse_args(&cmds, argv[i++]);
    if (cmds)
        ret = exec_cmds(&cmds, env);
    clear_list(&cmds);
    return (ret);
}




// gcc ./microshell.c -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out /usr/bin/ls ";" /usr/bin/echo HELLO WORLD

// $>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello world
// microshell

// ./a.out diff -U 3 user_output_test2 test2.output | cat -e        ///com o 'cat -e' retorna 0 ||| sem o 'cat -e' retorna 1 se forem arquivos diferentes, 0 se forem iguais e 2 se der erro.

// ./a.out /bin/echo "Hello World" | /usr/bin/tee output.txt | /usr/bin/wc -w

// ./a.out seq 1 10 "|" /usr/bin/xargs -n1 echo "Number:"

// ./a.out ls "|" grep microshell ";" ";" echo hello
