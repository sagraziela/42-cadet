/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:54:12 by root              #+#    #+#             */
/*   Updated: 2024/10/24 13:59:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFER_SIZE 10

typedef struct s_list
{
    char    c;
    struct s_list *next;
}   t_list;

char    *save_line(t_list **list)
{
    t_list  *temp;
    char    *line;
    int     len;
    int     i;

    len = 0;
    i = 0;
    temp = *list;
    while (*list && (*list)->c != '\n')
    {
        len++;
        printf("%c", (*list)->c);
        *list = (*list)->next;
    }
    *list = temp;
    line = malloc(sizeof(char) * (len + 1));
    line[len] = '\0';
    while (i < len)
    {
        line[i] = (*list)->c;
        temp = (*list)->next;
        free(*list);
        *list = temp;
        i++;
    }
    //printf("LINE: %s", line);
    return (line);
}

int    fill_list(t_list **list, char *buffer)
{
    int i;
    int line_brk;
    t_list  *new;
    t_list  *temp;

    temp = *list;
    i = 0;
    line_brk = 0;
    if (list)
    {
        while ((*list)->next)
            *list = (*list)->next;
    }
    while (buffer[i])
    {
        if (buffer[i] == '\n')
            line_brk = 1;
        new = malloc(sizeof(t_list));
        new->c = buffer[i];
        new->next = NULL;
        //printf("new->c = %c\n", new->c);
        (*list)->next = new;
        i++;
    }
    *list = temp;
    return (line_brk);
}

t_list  *read_file(int fd, t_list **list)
{
    char    *buffer;
    int     line_brk;
    int     rd;

    rd = 1;
    while (rd >= 0)
    {
        buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
        rd = read(fd, buffer, BUFFER_SIZE);
        if (rd <= 0)
        {
            free(buffer);
            printf("RD <= 0\n");
            break ;
        }
        else
        {
            buffer[rd] = '\0';
            line_brk = fill_list(list, buffer);
            free(buffer);
            if (line_brk)
                break ;
        }
    }
    return (*list);
}

char	  *get_next_line(int fd)
{
    static  t_list  *list;
    //t_list  *head;
    char    *line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = NULL;
    if (!list)
    {
        list = malloc(sizeof(t_list));
        list->c = '*';
        list->next = NULL;
    }
    //head = list;
    read_file(fd, &list);
    if (list->next)
        line = save_line(&list->next);
    else
        free(list);
    return (line);
}

int main(void)
{
    int fd;
    char *line;
    
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

// cc get_next_line.c -Wall -Wextra -Werror
