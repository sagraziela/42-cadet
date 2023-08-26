/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:13:22 by root              #+#    #+#             */
/*   Updated: 2023/08/26 14:08:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstadd(t_list *lst, char content)
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

t_list	*create_nodes(t_list *list, char *buffer, int rd)
{
	int		i;
	t_list	*node;

	i = 0;
	while (buffer[i] != '\0' && i < rd)
	{
		node = ft_lstadd(list, buffer[i]);
		i++;
	}
	return (node);
}

int	find_line_break_buffer(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n' || *buffer == '\0')
			return (1);
		buffer++;
	}
	return (0);
}

int	find_line_break_list(t_list *list)
{
	while (list)
	{
		if (list->content == '\n')
			return (1);
		list = list->next;
	}
	return (0);
}

size_t	find_line_len(t_list *list)
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
		if (list->content == '\n')
			break ;
		if (!temp)
			return (NULL);
		free(list);
		list = temp;
	}
	free(list);
	list = temp;
	return (list);
}

static t_list	**read_line(t_list *list, t_list **head, char *buffer, int fd)
{
	int		rd;

	if (!list)
	{
		list = NULL;
		rd = read(fd, buffer, BUFF_SIZE);
		if (rd == 0)
		{
			free(head);
			return (NULL);
		}
		if (find_line_break_buffer(buffer) == 1)
			rd = 0;
		list = ft_lstadd(list, buffer[0]);
		*head = list;
		list = create_nodes(list, (buffer + 1), rd);
	}
	else
	{
		*head = list;
		rd = 1;
	}
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFF_SIZE);
		if (rd == 0)
			break ;
		create_nodes(list, buffer, rd);
		if (find_line_break_buffer(buffer) == 1)
			break ;
	}
	return (head);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			**head;
	char			*buffer;
	char			*line;

	buffer = (char *)malloc(BUFF_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	head = (t_list **)malloc(sizeof(t_list *));
	if (!head)
		return (NULL);
	if ((list && !find_line_break_list(list)) || !list)
		head = read_line(list, head, buffer, fd);
	else if (find_line_break_list(list))
		*head = list;
	free(buffer);
	if (!head)
		return (NULL);
	else
	{
		list = *head;
		line = save_line(list);
		list = update_list(list);
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
//cc get_next_line4.c get_next_line.h