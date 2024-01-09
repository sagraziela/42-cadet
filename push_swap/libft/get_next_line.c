/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:42:54 by root              #+#    #+#             */
/*   Updated: 2024/01/09 12:34:25 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
		if (rd == 0)
		{
			free(buffer);
			return (head);
		}
		if (rd == -1)
			return (dealloc(list, buffer));
		buffer[rd] = '\0';
		head = ft_lstadd(list, buffer, head);
		list = head;
		if (!head)
			return (dealloc(head, buffer));
		free(buffer);
	}
	return (head);
}

static char	*quit(t_list **head, t_list **list)
{
	free(*head);
	*list = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	t_list			*head;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	head = create_node('*');
	if (list[fd])
	{
		head->next = list[fd];
		list[fd] = read_file(list[fd], fd, head->next);
		if (list[fd] == NULL)
			return (quit(&head, &list[fd]));
	}
	else if (!list[fd])
		head->next = read_file(list[fd], fd, head->next);
	list[fd] = head->next;
	if (!head->next)
		return (quit(&head, &list[fd]));
	line = save_line(list[fd]);
	list[fd] = head->next;
	list[fd] = update_list(&list[fd]);
	free(head);
	return (line);
}
