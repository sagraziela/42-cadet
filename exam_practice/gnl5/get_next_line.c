#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

typedef struct s_list
{
    char    c;
    struct s_list *next;
}   t_list;

/////////////////////////////////////////////////////////

char    *save_line(t_list **list)
{
    t_list  *temp;
    char    *line;
    int     len;
    int     i;

    temp = *list;
    i = 0;
    len = 0;
    while (*list)
    {
        len++;
        if ((*list)->c == '\n')
            break;
        *list = (*list)->next;
    }
    *list = temp;
    line = malloc(sizeof(char) * (len + 1));
    if (!line)
        return (NULL);
    while (i < len)
    {
        line[i] = (*list)->c;
        temp = (*list)->next;
        free(*list);
        *list = temp;
        i++;
    }
    line[len] = '\0';
    return (line);
}

int update_list(t_list **list, char *buffer)
{
    t_list  *temp;
    t_list  *new;
    int     i;
    int     line_brk;

    line_brk = 0;
    temp = *list;
    while ((*list)->next)
        *list = (*list)->next;
    i = 0;
    while (buffer[i])
    {
        if (buffer[i] == '\n')
            line_brk = 1;
        new = malloc(sizeof(t_list));
        new->c = buffer[i];
        new->next = NULL;
        (*list)->next = new;
        *list = (*list)->next;
        i++;
    }
    *list = temp;
    return (line_brk);
}

void    read_file(t_list **list, int fd)
{
    char    buffer[BUFFER_SIZE + 1];
    int     rd;
    int     line_brk;

    rd = 1;
    while (rd > 0)
    {
        rd = read(fd, buffer, BUFFER_SIZE);
        if (rd < 1)
            return ;
        buffer[rd] = '\0';
        line_brk = update_list(list, buffer);
        if (line_brk)
            return ;
    }
}

char	  *get_next_line(int fd)
{
    static t_list   *list;
    char            *line;

    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    line = NULL;
    if (!list)
    {
        list = malloc(sizeof(t_list));
        list->c = '*';
        list->next = NULL;
    }
    read_file(&list, fd);
    if (!list->next)
        free(list);
    else
        line = save_line(&list->next);
    return (line);
}

int main(void)
{
    char    *line;
    int     fd;

    fd = open("./test", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        printf("%s", line);
        free(line);
    }
}

// cc ./get_next_line.c -Wall -Wextra -Werror -g
