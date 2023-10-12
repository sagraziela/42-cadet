/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:43:39 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/30 13:44:06 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	find_line_len(t_list *list)
{
	size_t	counter;

	counter = 0;
	while (list)
	{
		counter++;
		if (list->content == '\n' || list->content == '\0')
			break ;
		list = list->next;
	}
	return (counter);
}

static char	*save_line(t_list *list)
{
	size_t	i;
	size_t	line_len;
	char	*line;

	line_len = find_line_len(list);
	line = (char *)ft_malloc((line_len + 1) * sizeof(char));
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

static t_list	*update_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list->next;
		if (list->content == '\n')
			break ;
		free(list);
		if (!temp)
			return (NULL);
		list = temp;
	}
	free(list);
	list = temp;
	return (list);
}

static t_list	**read_line(t_list *list, t_list **head, char *buffer, int fd)
{
	int		rd;
	char	*buff;

	if (!list)
	{
		list = NULL;
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == 0)
		{
			free(head);
			return (NULL);
		}
		if (find_line_break_buffer(buffer) == 1)
			rd = 0;
		list = ft_lstadd(list, buffer[0]);
		*head = list;
		buff = buffer + 1;
		list = create_nodes(list, buff, rd);
	}
	else
	{
		*head = list;
		rd = 1;
	}
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == 0)
			break ;
		create_nodes(list, buffer, rd);
		if (find_line_break_buffer(buffer) == 1)
			break ;
	}
	free(buffer);
	return (head);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			**head;
	char			*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_malloc((BUFFER_SIZE + 1) * sizeof(char));
	head = (t_list **)ft_malloc(sizeof(t_list *));
	if ((list && !find_line_break_list(list)) || !list)
		head = read_line(list, head, buffer, fd);
	else if (find_line_break_list(list))
	{
		*head = list;
		free(buffer);
	}
	if (!head)
	{
		free(head);
		free(list);
		free(buffer);
		return (NULL);
	}
	else
	{
		list = *head;
		line = save_line(list);
		list = update_list(list);
		free(head);
	}
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
		if (line == NULL)
			break ;
		free(line);
	}
	close(file);
}
// cc get_next_line1.c get_next_line_utils.c
// valgrind --leak-check=full --track-origins=yes ./a.out