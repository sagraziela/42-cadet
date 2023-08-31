/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:42:54 by root              #+#    #+#             */
/*   Updated: 2023/08/31 18:29:58 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*update_list(t_list *list)
{
	t_list	*temp;

	if (!list)
		return (NULL);
	while (list)
	{
		temp = list->next;
		if (list->content == '\n' || !temp)
			break ;
		free(list);
		list = temp;
	}
	free(list);
	list = temp;
	return (list);
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
			return (NULL);
		}
		buffer[rd] = '\0';
		head = ft_lstadd(list, buffer);
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
	head = NULL;
	if (list)
	{
		head = list;
		read_file(list, fd, head);
	}
	else
		head = read_file(list, fd, head);
	if (!head)
	{
		free(head);
		return (NULL);
	}
	list = head;
	line = save_line(list);
	list = update_list(head);
	free(head);
	return (line);
}

int	main(void)
{
	int		file;
	char	*line;

	file = open("file.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(file);
		printf("LINE: %s", line);
		free(line);
		if (line == NULL)
			break ;
	}
	close(file);
}

// cc -g -O0 get_next_line.c get_next_line_utils.c
// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out