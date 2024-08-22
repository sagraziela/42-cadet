/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:09:22 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/22 13:36:07 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./gnl.h"

void	fill_list(t_list **list, char *buffer)
{
	t_list	*temp;
	t_list	*new;
	int		i;

	temp = *list;
	i = 0;
	while((*list)->next)
		(*list) = (*list)->next;
	while (buffer[i])
	{
		new = malloc(sizeof(t_list));
		new->c = buffer[i];
		new->next = NULL;
		(*list)->next = new;
		*list = (*list)->next;
		//printf("%c", (*list)->c);
		i++;
	}
	//printf("\n");
	*list = temp;
}

int	read_file(int fd, t_list **list)
{
	char	*buffer;
	int		rd;
	int		i;

	rd = 1;
	while (rd > 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (0);
		rd = read(fd, buffer, BUFFER_SIZE);
		buffer[rd] = '\0';
		if (rd <= 0)
		{
			free(buffer);
			return (rd);
		}
		fill_list(list, buffer);
		i = 0;
		while (i < rd)
		{
			if (buffer[i] == '\n')
			{
				free(buffer);
				return (rd);
			}
			i++;
		}
		free(buffer);
	}
	return (fd);
}

char	*save_line(t_list **list)
{
	t_list	*temp;
	char	*line;
	size_t	i;
	size_t	length;

	temp = *list;
	length = 0;
	i = 0;
	while (*list && ((*list)->c != '\n' || (*list)->c != '\0'))
	{
		length++;
		*list = (*list)->next;
	}
	length++;
	line = malloc(sizeof(char) * length + 1);
	if (!line)
		return (NULL);
	*list = temp;
	while (i < length && *list)
	{
		line[i] = (*list)->c;
		temp = (*list)->next;
		free(*list);
		*list = temp;
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*head;
	char			*line;
	int				rd;

	if (!list)
	{
		list = malloc(sizeof(t_list));
		if (!list)
			return (NULL);
		list->c = '^';
		list->next = NULL;
	}
	head = list;
	line = NULL;
	rd = read_file(fd, &list);
	list = head;
	if (rd > 0)
		line = save_line(&list->next);
	else
	{
		while (list)
		{
			head = list->next;
			free(list);
			list = head;
		}
	}
	return (line);
}
