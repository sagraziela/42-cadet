#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

// https://github.com/TalhaAksoy/microshellExam/blob/main/main.c
// https://github.com/shackbei/microshell-42/blob/main/microshell.c

static int  ft_word_count(const char *s, char c)
{
    int count = 0;
    int in_word = 0;

    while (*s)
    {
        if (*s != c && in_word == 0)
        {
            count++;
            in_word = 1;
        }
        else if (*s == c)
            in_word = 0;
        s++;
    }
    return (count);
}

static char *ft_strndup(const char *s, int n)
{
    char *dup;
    int i = 0;

    dup = (char *)malloc(sizeof(char) * (n + 1));
    if (!dup)
        return (NULL);
    while (i < n)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char    **ft_split(const char *s, char c)
{
    int     i = 0;
    int     start = 0;
    int     word = 0;
    char    **res;

    if (!s || !(res = (char **)malloc(sizeof(char *) * (ft_word_count(s, c) + 1))))
        return (NULL);
    while (s[i])
    {
        if (s[i] != c && word == 0)
        {
            start = i;
            word = 1;
        }
        else if ((s[i] == c || s[i + 1] == '\0') && word == 1)
        {
            res[start] = ft_strndup(s + start, i - start + (s[i] != c));
            if (!res[start])
                return (NULL);
            start++;
            word = 0;
        }
        i++;
    }
    res[start] = NULL;
    return (res);
}

void    ft_strerr(char *str, char *arg)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(2, &str[i], 1);
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
}

//   TO STUDY  ::::
char    *ft_find_cmd(char *cmd, char *env[])
{
    int     i = 0;
    char    *path;
    char    *full_cmd;
    char    *dir;
    char    **paths;

    // Find PATH variable
    while (env[i] && strncmp(env[i], "PATH=", 5) != 0)
        i++;
    if (!env[i]) // No PATH found
        return NULL;

    path = env[i] + 5; // Skip "PATH="
    paths = ft_split(path, ':'); // Split PATH into directories

    i = 0;
    while (paths[i])
    {
        dir = paths[i];
        full_cmd = malloc(strlen(dir) + strlen(cmd) + 2); // Allocate space for path + "/" + cmd
        if (!full_cmd)
            return NULL;
        strcpy(full_cmd, dir);
        strcat(full_cmd, "/");
        strcat(full_cmd, cmd);

        if (access(full_cmd, X_OK) == 0) // Check if command is executable
            return full_cmd; // Found the valid path

        free(full_cmd);
        i++;
    }
    return NULL;
}

void    ft_exec(char *arg[], int i, int tmp_fd, char *env[])
{
    char    *cmd_path;

    arg[i] = NULL;
    dup2(tmp_fd, STDIN_FILENO);
    close(tmp_fd);
    if (strchr(arg[0], '/'))
        cmd_path = arg[0];
    else
        cmd_path = ft_find_cmd(arg[0], env);
    if (!cmd_path)
    {
        ft_strerr("error: command not found ", arg[0]);
        exit(127);
    }
    execve(cmd_path, arg, env);
    ft_strerr("error: cannot execute ", arg[0]);
    exit(1);
}

int main(int argc, char *argv[], char *env[])
{
    int     i;
    int     fd[2];
    int     tmp_fd;

    if (argc < 2)
        return 0;
    tmp_fd = dup(STDIN_FILENO);
    i = 0;
    while (argv[i] && argv[i + 1])
    {
        argv = &argv[i + 1];
        i = 0;
        while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        if (strcmp(argv[0], "cd") == 0)
        {
            printf("i = %d\n", i);
            if (i != 2)
                ft_strerr("error: cd: bad arguments", NULL);
            else if (chdir(argv[1]) != 0)
                ft_strerr("error: cd: cannot change directory to ", argv[1]);
        }
        else if (i > 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
        {
            if (fork() == 0)
                ft_exec(argv, i, tmp_fd, env);
            else 
            {
                close(tmp_fd);
                while (waitpid(-1, NULL, 0) > 0)
                    ;
                tmp_fd = dup(STDIN_FILENO);
            }
        }
        else if (i != 0 && strcmp(argv[i], "|") == 0)
        {
            pipe(fd);
            if (fork() == 0) //child
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                ft_exec(argv, i, tmp_fd, env);
            }
            else //parent
            {
                close(fd[1]);
                close(tmp_fd);
                tmp_fd = fd[0];
            }
        }
    }
    close(tmp_fd);
    return 0;
}

// gcc ./microshell.c -Wall -Wextra -Werror -g3
