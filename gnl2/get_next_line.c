/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:42:54 by root              #+#    #+#             */
/*   Updated: 2023/08/30 15:17:23 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*create_node(char c)
{
	t_list	*new_node;

	if (!c)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = c;
	new_node->next = NULL;
	return (new_node);
}

static t_list	*ft_lstadd(t_list *lst, char *buffer, t_list *head)
{
	t_list	*last;
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (!lst)
		{
			lst = create_node(buffer[i]);
			head = lst;
		}
		else
		{
			while ((lst)->next)
				lst = (lst)->next;
			last = lst;
			last->next = create_node(buffer[i]);
		}
		i++;
	}
	return (head);
}

static int	find_line_break(t_list *list)
{
	while (list)
	{
		if (list->content == '\n')
			return (1);
		list = list->next;
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

static t_list	*update_list(t_list *list)
{
	t_list	*temp;

	if (!list)
		return (NULL);
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

static t_list	**read_file(t_list *list, int fd, t_list **head)
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
		*head = ft_lstadd(list, buffer, *head);
		list = *head;
		free(buffer);
	}
	if (head)
		return (head);
	else
		return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			**head;
	char			*line;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!list)
		list = NULL;
	head = (t_list **)malloc(sizeof(t_list *));
	if (!head)
		return (NULL);
	if (list)
	{
		*head = list;
		read_file(list, fd, head);
	}
	else
		head = read_file(list, fd, head);
	if (!head)
		return (NULL);
	list = *head;
	line = save_line(list);
	list = *head;
	free(head);
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

// cc get_next_line.c
// valgrind --leak-check=full --track-origins=yes ./a.out