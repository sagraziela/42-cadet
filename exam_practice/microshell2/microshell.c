#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define STDIN   0
#define STDOUT  1
#define STDERR  2

#define TYPE_END    0
#define TYPE_PIPE   1
#define TYPE_BREAK  2

#define FD_OUT  0
#define FD_IN   1

// https://github.com/Glagan/42-exam-rank-04/blob/master/microshell/microshell.c

typedef struct s_list
{
    char    **args;
    int     length;
    int     type;
    int     pipes[2];
    struct s_list   *prev;
    struct s_list   *next;
}       t_list;

char    *ft_strdup(char *str)
{
    int     i;
    int     len;
    char    *dup;

    if (!str)
        return (NULL);
    len = 0;
    while (str[len])
        len++;
    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

int ft_strerr(char *msg, char *arg)
{
    int i;

    i = 0;
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

int exit_fatal()
{
    printf("FATAL ERROR\n");
    return (STDERR);
}

int add_arg(t_list *cmd, char *arg)
{
    char    **tmp;
    int     i;

    tmp = (char **)malloc(sizeof(char *) * (cmd->length + 2));
    if (!tmp)
        return (exit_fatal());
    i = 0;
    while (i < cmd->length)
    {
        tmp[i] = cmd->args[i];
        i++;
    }
    if (cmd->length > 0)
        free(cmd->args);
    cmd->args = tmp;
    cmd->args[i] = ft_strdup(arg);
    cmd->args[i + 1] = NULL;
    cmd->length++;
    return (EXIT_SUCCESS);
}

int list_push(t_list **cmds, char *arg)
{
    t_list  *new;

    new = (t_list*)malloc(sizeof(t_list));
    if (!new)
        return (exit_fatal());
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
    return (add_arg(new, arg));
}

int    parse_args(t_list **cmds, char *arg)
{
    int is_break;

    is_break = (strcmp(arg, ";") == 0);
    if (is_break && !*cmds)
        return (EXIT_SUCCESS);
    else if (!is_break && (!*cmds || (*cmds)->type > TYPE_END))
        return (list_push(cmds, arg));
    else if (strcmp(arg, "|") == 0)
        (*cmds)->type = TYPE_PIPE;
    else if (strcmp(arg, ";") == 0)
        (*cmds)->type = TYPE_BREAK;
    else
        return (add_arg(*cmds, arg));
    return (EXIT_SUCCESS);
    
}

char    *ft_find_cmd(char *cmd, char *env[])
{
    int     i = 0;
    int     j = 0;
    int     cmd_len;
    char    *path;
    char    *full_cmd;

    while (env[i] && strncmp(env[i], "PATH=", 5) != 0)
        i++;
    if (!env[i])
        return (NULL);
    path = env[i] + 5;
    //printf("%s\n\n", env[i]);
    //printf("Path ::: %s\n", path);
    i = 0;
    full_cmd = NULL;
    while (path[i])
    {
        if (path[i] == ':' || i == 0)
        {
            if (i > 0)
                i++;
            j = 0;
            while (path[i + j] && path[i + j] != ':')
                j++;
            cmd_len = 0;
            while (cmd[cmd_len])
                cmd_len++;
            full_cmd = malloc(sizeof(char) * (j + cmd_len + 2));
            cmd_len = 0;
            while (path[i] && path[i] != ':')
            {
                full_cmd[cmd_len] = path[i];
                cmd_len++;
                i++;
            }
            full_cmd[cmd_len++] = '/';
            j = 0;
            while (cmd[j])
            {
                full_cmd[cmd_len] = cmd[j];
                cmd_len++;
                j++;
            }
            full_cmd[cmd_len] = '\0';
            //printf("full_cmd = %s\n", full_cmd);
            if (access(full_cmd, X_OK) == 0)
                return (full_cmd);
            free(full_cmd);
        }
    }
    return (full_cmd);
}

int exec_cmd(t_list *cmd, char **env)
{
    pid_t   pid;
    int     ret;
    int     status;
    int     pipe_open;
    char    *cmd_path;

    ret = EXIT_FAILURE;
    pipe_open = 0;
    if (cmd->type == TYPE_PIPE || (cmd->prev && cmd->prev->type == TYPE_PIPE))
    {
        pipe_open = 1;
        if (pipe(cmd->pipes))
            exit_fatal();
    }
    pid = fork();
    if (pid < 0)
        return (exit_fatal());
    else if (pid == 0)
    {
        if (cmd->type == TYPE_PIPE && dup2(cmd->pipes[FD_IN], STDOUT) < 0)
            return (exit_fatal());
        if (cmd->prev && cmd->prev->type == TYPE_PIPE
                && dup2(cmd->prev->pipes[FD_OUT], STDIN) < 0)
            return (exit_fatal());
        cmd_path = ft_find_cmd(cmd->args[0], env);
        ret = execve(cmd_path, cmd->args, env);
        if (ret < 0)
            return (ft_strerr("error: cannot execute ", cmd->args[0]));
        // exit(ret);
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
                ret = WEXITSTATUS(status);
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
    while (*cmds)
    {
        tmp = *cmds;
        if (strcmp(tmp->args[0], "cd") == 0)
        {
            if (tmp->length < 2)
                return (ft_strerr("error: cd: bad arguments", NULL));
            else if (chdir(tmp->args[1]))
            {
                return (ft_strerr("error: cd: cannot change directory to ", tmp->args[1]));
            }
        }
        else
            ret = exec_cmd(tmp, env);
        if (!(*cmds)->next)
            break ;
        *cmds = (*cmds)->next;
    }
    return (ret);
}

void    clear_list(t_list **list)
{
    t_list *tmp;
    int     i;

    while ((*list)->prev)
        *list = (*list)->prev;
    while ((*list))
    {
        i = 0;
        tmp = (*list)->next;
        while ((*list)->args[i])
        {
            free((*list)->args[i]);
            i++;
        }
        free((*list)->args);
        free(*list);
        *list = tmp;
    }
}

int main(int argc, char **argv, char **env)
{
    t_list  *cmds;
    int     i;
    int     ret;

    if (argc == 1)
        return (0);
    cmds = NULL;
    ret = EXIT_SUCCESS;
    i = 1;
    while (i < argc)
        parse_args(&cmds, argv[i++]);
    if (cmds)
        ret = exec_cmds(&cmds, env);
    clear_list(&cmds);
    return (ret);
}

// gcc ./microshell.c -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out ls ; echo lala

