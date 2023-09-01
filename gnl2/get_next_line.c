/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:42:54 by root              #+#    #+#             */
/*   Updated: 2023/09/01 00:17:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*update_list(t_list **list)
{
	t_list	*temp;

	if (!list)
		return (NULL);
	while (*list)
	{
		temp = (*list)->next;
		if ((*list)->content == '\n' || !temp)
			break ;
		free(*list);
		*list = temp;
	}
	free(*list);
	*list = temp;
	return (*list);
}

static char	*save_line(t_list *list)
{
	size_t	i;
	size_t	line_len;
	char	*line;

	if (!list)
		return (NULL);
	line_len = find_line_len(list);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = list->content;
		list = list->next;
		i++;
	}
	line[i] = '\0';
	return (line);
}

static t_list	*read_file(t_list *list, int fd, t_list *head)
{
	int		rd;
	char	*buffer;

	rd = 1;
	while (!find_line_break(list))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		rd = read(fd, buffer, BUFFER_SIZE);
		if (!rd)
		{
			free(buffer);
			return (head);
		}
		buffer[rd] = '\0';
		head = ft_lstadd(list, buffer, head);
		list = head;
		if (!head)
		{
			dealloc(head, buffer);
			return (NULL);
		}
		free(buffer);
	}
	return (head);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*head;
	char			*line;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!list)
		list = NULL;
	head = create_node('*');
	if (list)
	{
		head->next = list;
		read_file(list, fd, head->next);
	}
	else if (!list)
		head->next = read_file(list, fd, head->next);
	list = head->next;
	if (!head->next)
	{
		free(head);
		return (NULL);
	}
	line = save_line(list);
	list = head->next;
	list = update_list(&list);
	free(head);
	return (line);
}

// cc -g3 get_next_line.c get_next_line_utils.c
// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out