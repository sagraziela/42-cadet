/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:51:32 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/21 18:15:42 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_lstadd(t_list **lst, char content)
{
	t_list	*last;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		while ((*lst)->next != NULL)
			*lst = (*lst)->next;
		last = *lst;
		last->next = new_node;
	}
	return (*lst);
}

static size_t	create_nodes(t_list **list,	char *buffer, size_t line_len)
{
	size_t	i;
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (0);
	head = *list;
	i = 0;
	while (buffer[i] != '\0')
	{
		ft_lstadd(list, buffer[i]);
		i++;
		if (buffer[i] == '\n')
			line_len = line_len + i + 1;
	}
	*list = head;
	return (line_len);
}

static int	find_line_break(char *buffer)
{
	int	i;
	int	break_line;

	i = 0;
	break_line = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			break_line = 1;
		i++;
	}
	return (break_line);
}

static char	*save_line(t_list **list, char *line, size_t line_len)
{
	size_t	i;

	i = 0;
	printf("%c\n", (*list)->content);
	while (list && i < line_len)
	{
		line[i] = (*list)->content;
		*list = (*list)->next;
	}
	printf("%s", line);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	**list;
	char			*buffer;
	char			*line;
	size_t			line_len;
	int				rd;

	buffer = (char *)malloc(BUFF_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!list)
		list = (t_list **)malloc(sizeof(t_list **));
	line_len = 0;
	rd = 1;
	while (rd > 0)
	{
		read(fd, buffer, BUFF_SIZE);
		line_len = create_nodes(list, buffer, line_len);
		if (find_line_break(buffer) == 1)
			break ;
		free(buffer);
	}
	printf("LINE_LEN: %zu\n", line_len);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	line = save_line(list, line, line_len);
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
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
	close(file);
}

//cc get_next_line3.c get_next_line.h