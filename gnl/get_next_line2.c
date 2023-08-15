/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:40:06 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/15 17:22:22 by gde-souz         ###   ########.fr       */
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

static char	*cut_last_buff(t_list **list, char *buffer, int rd)
{
	int		i;
	char	*last_buffer;

	i = 0;
	last_buffer = malloc(rd + 1);
	if (!last_buffer)
		return (NULL);
	while (buffer[i] != '\0')
	{
		last_buffer[i] = buffer[i];
		i++;
	}
	last_buffer[i] = '\0';
	ft_lstadd(list, last_buffer);
	return (last_buffer);
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

static int	increment_list(t_list **list, char *buffer, int rd)
	{
	int		line_break;
	int		i;

	i = 0;
	if (rd < BUFF_SIZE)
	{
		cut_last_buff(list, buffer, rd);
		free(buffer);
		return (1);
	}
	else
	{
		line_break = find_line_break(buffer);
		buffer[rd] = '\0';
		printf ("%s\n", buffer);
		ft_lstadd(list, buffer);
		return (line_break);
	}
}

t_list	*find_next_line(t_list **list, int fd)
{
	int		rd;
	int		end_line;
	char	*buffer;

	rd = 1;
	while (rd > 0)
	{
		buffer = malloc(BUFF_SIZE + 1);
		if (!buffer)
			return (NULL);
		if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buffer, 0) < 0)
			return (NULL);
		rd = read(fd, buffer, BUFF_SIZE);
		if (!rd)
		{
			free(buffer);
			return (NULL);
		}
		end_line = increment_list(list, buffer, rd);
		if (end_line >= 0)
		{
			printf("FOUND LINE BREAK\n");
			return (*list);
		}
	}
	return (*list);
}

char	*get_next_line(int fd)
{
	static t_list	**list;

	if (!list)
	{
		list = (t_list **)malloc(sizeof(size_t *));
		if (!list)
			return (NULL);
	}
	find_next_line(list, fd);
	//update_list(list);
	return ((*list)->content);
}

int	main(void)
{
	int	file;

	file = open("file.txt", O_RDONLY);
	get_next_line(file);
	get_next_line(file);
	get_next_line(file);
	close(file);
}
