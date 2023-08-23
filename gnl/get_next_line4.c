/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:04:06 by root              #+#    #+#             */
/*   Updated: 2023/08/23 12:20:59 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	if (!s)
	{
		return (NULL);
	}
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

static t_list	*ft_lstadd(t_list *lst, char content)
{
	t_list	*last;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ((t_list *)0);
	new_node->content = content;
	new_node->next = NULL;
	if (lst == NULL)
		lst = new_node;
	else
	{
		while (lst->next)
			lst = lst->next;
		last = lst;
		last->next = new_node;
	}
	return (lst);
}

static t_list	*create_nodes(t_list *list, char *buffer)
{
	size_t	i;
	t_list	*node;

	i = 0;
	while (buffer[i] != '\0')
	{
		node = ft_lstadd(list, buffer[i]);
		i++;
	}
	return (node);
}

static int	find_line_break(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n')
			return (1);
		buffer++;
	}
	return (0);
}

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
	char	line[line_len];

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

static t_list	*update_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list->next;
		if (list->content == '\n' || list->content == '\0')
			break ;
		free(list);
		list = temp;
	}
	free(list);
	list = temp;
	return (list);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			**head;
	char			*buffer;
	char			*line;
	int				rd;

	buffer = (char *)malloc(BUFF_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	rd = 1;
	head = (t_list **)malloc(sizeof(t_list *));
	if (!head)
		return (NULL);
	if (list)
		*head = list;
	else
	{
		list = NULL;
		rd = read(fd, buffer, BUFF_SIZE);
		list = ft_lstadd(list, buffer[0]);
		*head = list;
		list = create_nodes(list, (buffer + 1));
		if (find_line_break(buffer) == 1)
			rd = 0;
	}
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFF_SIZE);
		create_nodes(list, buffer);
		if (find_line_break(buffer) == 1)
			break ;
		ft_memset(buffer, 0, BUFF_SIZE);
	}
	free(buffer);
	list = *head;
	line = save_line(list);
	list = update_list(list);
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
//cc get_next_line4.c get_next_line.h
