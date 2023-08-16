/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:40:06 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/16 18:15:22 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void	ft_lstadd(t_list **lst, void *content)
{
	t_list	*last;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = content;
	new_node->next = NULL;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new_node;
	}
}

static int	find_line_break(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

static void	join_buffers(t_list **list, char *line, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < n)
	{
		while ((*list)->content[j] != '\0')
		{
			line[i] = (*list)->content[j];
			i++;
			j++;
		}
		*list = (*list)->next;
		j = 0;
	}
}

static int	increment_list(t_list **list, char *buffer)
{
	int		line_break;
	int		i;
	int		line_len;
	char	*line;

	i = 0;
	line_len = 0;
	line_break = find_line_break(buffer);
	ft_lstadd(list, buffer);
	while (*list)
	{
		while ((*list)->content[i] != '\0' || (*list)->content[i] != '\n')
			i++;
		line_len += i;
		i = 0;
		printf("%s\n", (*list)->content);
		printf("END NODE\n");
		*list = (*list)->next;
	}
	line = (char *)malloc(line_len + 1 * sizeof(char));
	if (!line)
		return ;
	join_buffers(list, line, line_len);
	return (line_break);
}

static char	*fill_buffer(t_list **list, int fd, char *buffer)
{
	int		rd;
	int		end_line;

	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFF_SIZE);
		buffer[BUFF_SIZE] = '\0';
		if (!rd)
			return (NULL);
		end_line = increment_list(list, buffer);
		if (end_line >= 0)
		{
			return (buffer);
		}
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static t_list	**list;
	char			buffer[BUFF_SIZE + 1];
	char			*line;

	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!list)
	{
		list = (t_list **)malloc(sizeof(t_list **));
	}
	line = fill_buffer(list, fd, buffer);
	//update_list(list);
	return (line);
}

int	main(void)
{
	int	file;

	file = open("file.txt", O_RDONLY);
	get_next_line(file);
	close(file);
}
//cc get_next_line2.c get_next_line.h
