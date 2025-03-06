#include <stdlib.h>
#include <unistd.h>
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
    struct s_list   *prev;
    struct s_list   *next;
}       t_list;


int fatal_error(void)
{
    write(2, "Fatal error\n", 13);
    return (STDERR);
}

int ft_strerr(char *msg, char *arg)
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
    return (STDERR);
}

char    *ft_strdup(char *str)
{
    char    *dup;
    int     i;

    i = 0;
    dup = NULL;
    while (str[i])
        i++;
    dup = malloc(sizeof(char) * i + 1);
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
    char    **new_args;
    int     i;

    i = 0;
    new_args = malloc(sizeof(char *) * (cmd->length + 2));
    if (!new_args)
        return (fatal_error());
    while (i < cmd->length)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[i] = ft_strdup(arg);
    free(cmd->args);
    new_args[i + 1] = NULL;
    cmd->length++;
    cmd->args = new_args;
    return (EXIT_SUCCESS);
}

int list_push(t_list **cmds, char *arg)
{
    t_list *new;

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

int    parse_args(t_list **cmds, char *arg)
{
    int is_break;

    is_break = 0;
    if (strcmp(arg, ";") == 0)
        is_break = 1;
    if (!*cmds && is_break)
        return (EXIT_SUCCESS);
    else if (!is_break && (!*cmds || (*cmds)->type > TYPE_END))
        return (list_push(cmds, arg));
    else if (strcmp(arg, ";") == 0)
        (*cmds)->type = TYPE_BREAK;
    else if (strcmp(arg, "|") == 0)
        (*cmds)->type = TYPE_PIPE;
    else
        return (add_arg(*cmds, arg));
    return (EXIT_SUCCESS);
}

int exec_cmd(t_list *cmd, char **env)
{
    pid_t   pid;
    int     ret;
    int     status;
    int     pipe_open;
    char    *path_cmd;

    ret = EXIT_FAILURE;
    pipe_open = 0;
    if (cmd->type == TYPE_PIPE || (cmd->prev && cmd->prev->type == TYPE_PIPE))
    {
        pipe_open = 1;
        if (pipe(cmd->pipes))
            return (fatal_error());
    }
    pid = fork();
    if (pid < 0)
        return (fatal_error());
    if (pid == 0)
    {
        if (cmd->type == TYPE_PIPE && dup2(cmd->pipes[FD_IN], STDOUT) < 0)
            return (fatal_error());
        else if (cmd->prev && cmd->prev->type == TYPE_PIPE
            && dup2(cmd->prev->pipes[FD_OUT], STDIN) < 0)
            return (fatal_error());
        path_cmd = "/usr/bin/ls"; //get_cmd_path();
        ret = execve(path_cmd, cmd->args, env);
        exit(fatal_error());
    }
    else
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
                return (WEXITSTATUS(status)); // ver como isso funciona -- erro valgrind ao executar "./a.out cd lala"
        }
    }
    return (ret);
}

int exec_cmds(t_list **cmds, char **env)
{
    t_list  *tmp;
    int     ret;

    while ((*cmds)->prev)
        *cmds = (*cmds)->prev;
    ret = EXIT_FAILURE;
    tmp = *cmds;
    while (tmp)
    {
        if (strcmp(tmp->args[0], "cd") == 0)
        {
            if (tmp->length != 2)
                return (ft_strerr("error: cd: bad arguments", NULL));
            else if (chdir(tmp->args[1]) != 0)
                return (ft_strerr("error: cd: cannot change directory to ", tmp->args[1]));
        }
        else
            ret = exec_cmd(tmp, env);
        tmp = tmp->next;
    }
    return (ret);
}

void    clear_list(t_list **list)
{
    t_list  *tmp;
    int     i;

    while ((*list))
    {
        i = 0;
        while ((*list)->args[i])
            free((*list)->args[i++]);
        free((*list)->args);
        tmp = (*list)->prev;
        free(*list);
        *list = tmp;
    }
}

int main(int argc, char **argv, char **env)
{
    t_list  *cmds;
    int     i;
    int     ret;

    if (argc < 2)
        return (EXIT_SUCCESS);
    i = 1;
    ret = EXIT_SUCCESS;
    cmds = NULL;
    while (i < argc)
        parse_args(&cmds, argv[i++]);
    if (cmds)
        ret = exec_cmds(&cmds, env);
    clear_list(&cmds);
    return (ret);
}


//  gcc ./microshell.c -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out ls ; echo lala
