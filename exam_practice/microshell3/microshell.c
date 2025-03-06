#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define TYPE_END 0
#define TYPE_PIPE 1
#define TYPE_BREAK 2

#define FD_OUT   0
#define FD_IN    1

typedef struct s_list
{
    char    **args;
    int     type;
    int     length;
    int     pipes[2];
    struct s_list   *prev;
    struct s_list   *next;
}       t_list;

int    ft_strerr(char *msg, char *arg)
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

int fatal_exit(void)
{
    write(2, "FATAL ERROR\n", 13);
    return (STDERR);
}

char    *ft_strdup(char *str)
{
    int     i;
    char    *dup;

    i = 0;
    while (str[i])
        i++;
    dup = malloc(sizeof(char) * (i + 1));
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

    new_args = (char **)malloc(sizeof(char *) * (cmd->length + 2));
    if (!new_args)
        return (fatal_exit());
    i = 0;
    while (i < cmd->length)
    {
        new_args[i] = ft_strdup(cmd->args[i]);
        free(cmd->args[i]);
        i++;
    }
    if (cmd->args)
        free(cmd->args);
    new_args[i++] = ft_strdup(arg);
    new_args[i] = '\0';
    cmd->args = new_args;
    cmd->length++;
    return (EXIT_SUCCESS);
}

int push_list(t_list **cmds, char *arg)
{
    t_list  *new;

    new = (t_list *)malloc(sizeof(t_list));
    if (!new)
        return (fatal_exit());
    new->args = NULL;
    new->type = TYPE_END;
    new->length = 0;
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

    is_break = 0;
    if (strcmp(arg, ";") == 0)
        is_break = 1;
    if (is_break && !*cmds)
        return (EXIT_SUCCESS);
    else if (!is_break && (!*cmds || (*cmds)->type > TYPE_END))
        return (push_list(cmds, arg));
    else if (*cmds && strcmp(arg, "|") == 0)
        (*cmds)->type = TYPE_PIPE;
    else if (*cmds && is_break)
        (*cmds)->type = TYPE_BREAK;
    else
        return (add_arg(*cmds, arg));
    return (EXIT_SUCCESS);
}

char    *get_cmd_path(char *cmd, char **env)
{
    int     i;
    int     j;
    int     len;
    char    *path;
    char    *full_path;

    i = 0;
    while (strncmp(env[i], "PATH=", 5) != 0)
        i++;
    path = env[i] + 5;
    len = 0;
    while (cmd[len])
        len++;
    i = 0;
    j = 0;
    while (path[i])
    {
        if (i == 0 || path[i] == ':')
        {
            i++;
            j = 0;
            while (path[i + j] != ':')
                j++;
        }
        full_path = malloc(sizeof(char) * (j + len + 2));
        if (!full_path)
            return (NULL);
        j = 0;
        while (path[i + j] && path[i + j] != ':')
        {
            full_path[j] = path[i + j];
            j++;
        }
        i += j;
        full_path[j++] = '/';
        len = 0;
        while (cmd[len])
            full_path[j++] = cmd[len++];
        full_path[j] = '\0';
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
    }
    return(NULL);
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
            return (fatal_exit());
    }
    pid = fork();
    if (pid < 0)
        return (fatal_exit());
    else if (pid == 0)
    {
        if (cmd->type == TYPE_PIPE && dup2(cmd->pipes[FD_IN], STDOUT) < 0)
            return (fatal_exit());
        if (cmd->prev && cmd->prev->type == TYPE_PIPE
            && dup2(cmd->pipes[FD_OUT], STDIN) < 0)
            return (fatal_exit());
        path_cmd = get_cmd_path(cmd->args[0], env);
        ret = execve(path_cmd, cmd->args, env);
        if (ret < 0)
            return (ft_strerr("error: cannot execute ", cmd->args[0]));
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
                ret = WIFEXITED(status);
        }
    }
    return (ret);
}

int exec_cmds(t_list **cmds, char **env)
{
    t_list  *tmp;
    int     ret;

    ret = EXIT_SUCCESS;
    while (*cmds && (*cmds)->prev)
        *cmds = (*cmds)->prev;
    tmp = *cmds;
    while ((tmp))
    {
        if (strcmp(tmp->args[0], "cd") == 0)
        {
            if (tmp->length != 2)
                return (ft_strerr("error: cd: bad arguments", NULL));
            if (chdir(tmp->args[1]))
                return (ft_strerr("error: cd: cannot change directory to ", tmp->args[1]));
        }
        else
            ret = exec_cmd(tmp, env);
        tmp = tmp->next;
    }
    return (ret);
}

void    clear(t_list **cmds)
{
    t_list  *tmp;
    int     i;

    while (*cmds)
    {
        if ((*cmds)->args)
        {
            i = 0;
            while ((*cmds)->args[i])
                free((*cmds)->args[i++]);
            free((*cmds)->args);
        }
        tmp = (*cmds)->next;
        free(*cmds);
        *cmds = tmp;
    }
}

int main(int argc, char **argv, char **env)
{
    t_list *cmds;
    int     ret;
    int     i;

    if (argc < 2)
        return (0);
    cmds = NULL;
    ret = EXIT_SUCCESS;
    i = 1;
    while (i < argc)
        parse_args(&cmds, argv[i++]);
    if (cmds)
        ret = exec_cmds(&cmds, env);
    clear(&cmds);
    return (ret);
}

// gcc ./microshell.c -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out ls ; echo lala
