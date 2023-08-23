/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:04:06 by root              #+#    #+#             */
/*   Updated: 2023/08/22 22:46:38 by root             ###   ########.fr       */
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

static void	ft_lstadd(t_list *lst, char content)
{
	t_list	*last;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = content;
	new_node->next = NULL;
	if (lst == NULL)
	{
		lst = new_node;
		head = &lst;
	}
	else
	{
		while (lst->next)
			lst = lst->next;
		last = lst;
		last->next = new_node;
	}
	return ;
}

static void	create_nodes(t_list *list, char *buffer)
{
	size_t	i;

	i = 0;
	//printf("--create_nodes--\n");
	while (buffer[i] != '\0')
	{
		ft_lstadd(list, buffer[i], head);
		i++;
	}
	return ;
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
	t_list	*aux_list;

	counter = 0;
	aux_list = list;
	printf("--find_line_len--\n");
	while (aux_list)
	{
		printf("%c", aux_list->content);
		counter++;
		if (aux_list->content == '\n' || aux_list->content == '\0')
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

	line_len = find_line_len(list);
	printf("LINE_LEN: %zu\n", line_len);
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	i = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
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
		list = (t_list *)malloc(sizeof(t_list));
	head = 
	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFF_SIZE);
		printf("buffer: %s\n", buffer);
		create_nodes(*list, buffer);
		if (find_line_break(buffer) == 1)
			break ;
		ft_memset(buffer, 0, BUFF_SIZE);
	}
	free(buffer);
	line = save_line(head);
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
