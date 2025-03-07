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
#define FD_IN   1

typedef struct s_list
{
    char    **args;
    int     length;
    int     type;
    int     pipes[2];
    struct s_list *prev;
    struct s_list *next;
}   t_list;

void    clear_list(t_list **list)
{
    t_list  *tmp;
    int     i;

    if (!list)
        return ;
    if ((*list)->prev)
    {
        while ((*list)->prev)
            *list = (*list)->prev;
    }
    while (*list)
    {
        //printf("AQUI -\n");
        i = 0;
        tmp = (*list)->next;
        if ((*list)->args)
        {
            while ((*list)->args[i])
                free((*list)->args[i++]);
        }
        free((*list)->args);
        free(*list);
        *list = tmp;
    }
}

int fatal_error(t_list *list)
{
    write(2, "error: fatal\n", 14);
    clear_list(&list);
    return (EXIT_FAILURE);
}

int ft_strerr(char *msg, char *arg, t_list *list)
{
    int i;

    i = 0;
    while (msg[i])
        write(2, &msg[i++], 1);
    if (arg)
    {
        i = 0;
        while (arg[i])
            write(2, &arg[i++], 1);
    }
    write(2, "\n", 1);
    clear_list(&list);
    return (EXIT_FAILURE);
}

char    *ft_strdup(char *str)
{
    char    *dup;
    int     i;

    i = 0;
    dup = NULL;
    while (str[i])
        i++;
    dup = (char *)malloc(sizeof(char) * i + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}
int add_arg(t_list *cmd, char *arg)
{
    int i;
    char **new_args;

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
    new_args[i++] = ft_strdup(arg);
    new_args[i] = NULL;
    cmd->args = new_args;
    cmd->length++;
    return (EXIT_SUCCESS);
}

int list_push(t_list **cmds, char *arg)
{
    t_list  *new;
    
    //printf("push: %s\n", arg);
    new = malloc(sizeof(t_list));
    if (!new)
        return (fatal_error(*cmds));
    new->args = NULL;
    new->length = 0;
    new->type  = TYPE_END;
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
    {
        //printf("add_arg: %s\n", arg);
        return (add_arg(*cmds, arg));
    }
    return (EXIT_SUCCESS);
}

int exec_cmd(t_list *cmd, char **env)
{
    pid_t   pid;
    int     status;
    int     pipe_open;
    int     ret;

    ret = EXIT_SUCCESS;
    pipe_open = 0;
    if (cmd->type == TYPE_PIPE || (cmd->prev && cmd->prev->type == TYPE_PIPE))
    {
        pipe_open = 1;
        if (pipe(cmd->pipes))
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
            && dup2(cmd->prev->pipes[FD_OUT], STDIN) < 0)
            return (fatal_error(cmd));
        ret = execve(cmd->args[0], cmd->args, env);
        exit(ft_strerr("error: cannot execute ", cmd->args[0], cmd));
        //return (ft_strerr("error: cannot execute ", cmd->args[0]));
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
            if (WIFEXITED(status))
                return (WEXITSTATUS(status));
        }
    }
    return (ret) ;
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
                return (ft_strerr("error: cd: bad arguments", NULL, *cmds));
            if (chdir((*cmds)->args[1]))
                return (ft_strerr("error: cd: cannot change directory to ", (*cmds)->args[1], *cmds));
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

    if (argc < 2)
        return (EXIT_SUCCESS);
    cmds = NULL;
    i = 1;
    while (argv[i])
        parse_args(&cmds, argv[i++]);
    if (cmds)
        ret = exec_cmds(&cmds, env);
    clear_list(&cmds);
    return(ret);
}


// gcc ./microshell -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out /usr/bin/ls ";" /usr/bin/echo HELLO WORLD

// $>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello world
// microshell