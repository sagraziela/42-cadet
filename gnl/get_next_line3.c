/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:51:32 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/22 20:05:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_lstadd(t_list **lst, char content)
{
	t_list	*last;
	t_list	*new_node;
	t_list	*head;

	head = *lst;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	printf("%c", new_node->content);
	if (*lst == NULL)
	{
		*lst = new_node;
		head = *lst;
	}
	else
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		last = *lst;
		last->next = new_node;
	}
	return (head);
}

static t_list	*create_nodes(t_list **list, char *buffer)
{
	size_t	i;
	t_list	*head;

	i = 0;
	if (*list)
		head = *list;
	else
	{
		head = ft_lstadd(list, buffer[i]);
		i++;
	}
	while (buffer[i] != '\0')
	{
		ft_lstadd(list, buffer[i]);
		i++;
	}
	return (head);
}

static size_t	find_line_break(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static size_t	find_line_len(t_list *list)
{
	size_t	counter;
	t_list	*aux_list;

	counter = 0;
	printf("ln 82: %c\n", list->content);
	aux_list = list;
	while (aux_list)
	{
		counter++;
		if (aux_list->content == '\n')
			break ;
		aux_list = aux_list->next;
	}
	return (counter);
}

static char	*save_line(t_list *list)
{
	size_t	i;
	size_t	line_len;
	char	*line;
	t_list	*aux_node;

	line_len = find_line_len(list);
	printf("ln 103: %c\n", list->content);
	printf("LINE_LEN: %zu\n", line_len);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = list->content;
		aux_node = list->next;
		free(list);
		list = aux_node;
		i++;
	}
	line[i] = '\0';
	while (list)
	{
		printf("--in_save_line-- %c", list->content);
		list = list->next;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	**list;
	t_list			*head;
	char			*buffer;
	char			*line;
	int				rd;

	buffer = (char *)malloc(BUFF_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!list)
		list = (t_list **)malloc(sizeof(t_list **));
	rd = 1;
	head = *list;
	while (rd > 0)
	{
		read(fd, buffer, BUFF_SIZE);
		*list = create_nodes(list, buffer);
		if ((*list)->next == NULL)
			head = *list;
		if (find_line_break(buffer) == 1)
		{
			free(buffer);
			break ;
		}
		free(buffer);
	}
	line = save_line(head);
	//printf("--in_gnl-- %c\n", (*list)->content);
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
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	close(file);
}

//cc get_next_line3.c get_next_line.h