/bin/ls
a.out
microshell
microshell.c
out.res
test.sh
test2.output
user_output_test2

/bin/cat microshell.c
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

#ifdef TEST_SH
# define TEST		1
#else
# define TEST		0
#endif

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
    if (list)
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
        return (add_arg(*cmds, arg));
    return (EXIT_SUCCESS);
}

char    *get_cmd_path(char *cmd)
{
    char    *full_cmd;
    char    *path;
    int     i;
    int     len;

    if (cmd[0] == '/' && cmd[1])
        return (ft_strdup(cmd));
    path = "/usr/bin/";
    len = 0;
    while (cmd[len])
        len++;
    full_cmd = malloc(sizeof(char) * len + 9 + 1);
    if (!cmd)
        return (NULL);
    i = 0;
    while (path[i])
    {
        full_cmd[i] = path[i];
        i++;
    }
    len = 0;
    while (cmd[len])
    {
        full_cmd[i++] = cmd[len++];
    }
    full_cmd[i] = '\0';
    return (full_cmd);
}

int exec_cmd(t_list *cmd, char **env)
{
    pid_t   pid;
    int     status;
    int     pipe_open;
    int     ret;
    char    *full_cmd;

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
        full_cmd = get_cmd_path(cmd->args[0]);
        if (!full_cmd)
            return (fatal_error(cmd));
        ret = execve(full_cmd, cmd->args, env);
        exit(ft_strerr("error: cannot execute ", cmd->args[0], cmd));
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


// gcc ./microshell.c -Wall -Wextra -Werror -g3

// valgrind --leak-check=full --show-leak-kinds=all ./a.out /usr/bin/ls ";" /usr/bin/echo HELLO WORLD

// $>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello world
// microshell

// ./a.out diff -U 3 user_output_test2 test2.output | cat -e
/bin/ls microshell.c
microshell.c

/bin/ls salut

;

; ;

; ; /bin/echo OK
OK

; ; /bin/echo OK ;
OK

; ; /bin/echo OK ; ;

; ; /bin/echo OK ; ; ; /bin/echo OK

/bin/ls | /usr/bin/grep microshell
microshell
microshell.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro
microshell
microshell.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro
microshell
microshell.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell
microshell
microshell.c

/bin/ls ewqew | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo
dernier


/bin/ls | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo ftest ;
     1	microshell
     2	microshell.c
dernier
ftest

/bin/echo ftest ; /bin/echo ftewerwerwerst ; /bin/echo werwerwer ; /bin/echo qweqweqweqew ; /bin/echo qwewqeqrtregrfyukui ;
ftest
ftewerwerwerst
werwerwer
qweqweqweqew
qwewqeqrtregrfyukui

/bin/ls ftest ; /bin/ls ; /bin/ls werwer ; /bin/ls microshell.c ; /bin/ls subject.fr.txt ;
a.out
leaks.res
microshell
microshell.c
out.res
test.sh
test2.output
user_output_test2
microshell.c

/bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ;
microshell
microshell.c
microshell
microshell.c
microshell
microshell.c
microshell
microshell.c

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b ; /bin/cat subject.fr.txt ;

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt ;

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt

/bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt

; /bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt

blah | /bin/echo OK
OK

blah | /bin/echo OK ;
OK

