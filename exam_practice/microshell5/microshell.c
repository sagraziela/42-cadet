#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#define TYPE_END 0
#define TYPE_BREAK 1
#define TYPE_PIPE 2

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define FD_OUT 0
#define FD_IN 1

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
    return (EXIT_FAILURE);
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
    int i;
    char **new_args;

    new_args = (char **)malloc(sizeof(char *) * (cmd->length + 2));
    if (!new_args)
        return (fatal_error());
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
    
    new = malloc(sizeof(t_list));
    if (!new)
        return (fatal_error());
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
        return (fatal_error());
    else if (!*cmds || (*cmds)->type > TYPE_END)
        return (list_push(cmds, arg));
    else if (is_pipe)
        (*cmds)->type = TYPE_PIPE;
    else if (is_break)
        (*cmds)->type = TYPE_BREAK;
    else
        return (add_arg(*cmds, arg));
    return (EXIT_SUCCESS);
}

// char    *get_cmd_path(char *arg, char **env)
// {
//     int     i;
//     int     j;
//     int     arg_len;
//     char    *path;
//     char    *cmd_path;

//     arg_len = 0;
//     while (arg[arg_len])
//         arg_len++;
//     i = 0;
//     while (env[i])
//     {
//         if (strncmp(env[i], "PATH=", 5) == 0)
//             break ;
//         i++;
//     }
//     path = env[i] + 5;
//     i = 0;
//     while (path[i])
//     {
//         if (i == 0 || path[i] == ':')
//         {
//             j= 0;
//             if (path[i] == ':')
//                 i++;
//             while (path[i + j] && path[i + j] != ':')
//                 j++;
//         }
//         cmd_path = malloc(sizeof(char) * j + arg_len + 2);
//         if(!cmd_path)
//             return (NULL);
//         j = 0;
//         while (path[i + j] && path [i + j] != ':')
//         {
//             cmd_path[j] = path[i + j];
//             j++;
//         }
//         i = i + j;
//         cmd_path[j++] = '/';
//         arg_len = 0;
//         while (arg[arg_len])
//             cmd_path[j++] = arg[arg_len++];
//         cmd_path[j] = '\0';
//         if (access(cmd_path, X_OK)  == 0)
//             return (cmd_path);
//         free(cmd_path);
//     }
//     return (NULL);
// }

int exec_cmd(t_list *cmd, char **env)
{
    pid_t   pid;
    int     ret;
    int     status;
    int     pipe_open;
    char    *path_cmd;

    ret = EXIT_SUCCESS;
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
    if (pid == 0) // exec processo filho
    {
        if (cmd->type == TYPE_PIPE && dup2(cmd->pipes[FD_IN], STDOUT) < 0)
            return (fatal_error());
        if (cmd->prev && cmd->prev->type == TYPE_PIPE
            && dup2(cmd->prev->pipes[FD_OUT], STDIN) < 0)
            return (fatal_error());
        path_cmd = cmd->args[0];
        if (!path_cmd)
            return (ft_strerr("error: command not found: ", cmd->args[0]));
        execve(path_cmd, cmd->args, env);
        ret = EXIT_FAILURE;
        exit(fatal_error());
    }
    if (pid > 0) // exec processo pai
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
    return (ret);
}

int exec_cmds(t_list **cmds, char **env)
{
    t_list  *tmp;
    int     ret;

    while ((*cmds)->prev)
        *cmds = (*cmds)->prev;
    tmp = *cmds;
    ret = EXIT_FAILURE;
    while (*cmds)
    {
        if (strcmp((*cmds)->args[0], "cd") == 0)
        {
            if ((*cmds)->length != 2)
            {
                ft_strerr("error: cd: bad arguments", NULL);
                //continue ;
            }
            else if (chdir((*cmds)->args[1]))
                return(ft_strerr("error: cd: cannot change directory to ", (*cmds)->args[1]));
            else
                ret = EXIT_SUCCESS;
        }
        else
            ret = exec_cmd(*cmds, env);
        //printf("%s\n", (*cmds)->args[0]);
        //printf("RET = %d\n", ret);
        *cmds = (*cmds)->next;
    }
    *cmds = tmp;
    return (ret);
}

void    clear_list(t_list **list)
{
    t_list  *tmp;
    int     i;

    while (*list)
    {
        i = 0;
        tmp = (*list)->prev;
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


//  gcc ./microshell.c -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out ls ; echo lala

// $>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
// microshell
// i love my microshell
// $>

// >./microshell 
