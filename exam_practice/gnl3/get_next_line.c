/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:59:21 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/28 13:07:22 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

char	*save_line(t_list **list)
{
	t_list	*temp;
	char	*line;
	int		len;
	int		i;

	temp = *list;
	while ((*list)->next)
	{
		len++;
		//printf("%c", (*list)->c);
		if ((*list)->c == '\n' || (*list)->c == '\0')
			break;
		*list = (*list)->next;
	}
	*list = temp;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = (*list)->c;
		i++;
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
	line[len] = '\0';
	return (line);
}

void	add_node(t_list **list, char content)
{
	t_list	*new;
	t_list	*temp;

	temp = *list;
	while ((*list)->next)
		*list = (*list)->next;
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->c = content;
	new->next = NULL;
	(*list)->next = new;
	printf("%c", new->c);
	*list = temp;
}

int	read_file(t_list **list, int fd)
{
	int		rd;
	int		i;
	char	buffer[BUFFER_SIZE + 1];
	t_bool	found_brkline;

	rd = 1;
	i = 0;
	found_brkline = FALSE;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
			return (rd);
		buffer[rd] = '\0';
		//printf("BUFFER: %s\n", buffer);
		while (i < rd)
		{
			add_node(list, buffer[i]);
			if (buffer[i] == '\n')
				found_brkline = TRUE;
			i++;
		}
		if (found_brkline)
			break ;
	}
	return (rd);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*head;
	char			*line;
	int				rd;

	//printf("CHEGOU AQUI fd %d\n", fd);
	if (BUFFER_SIZE == 0 || fd < 1)
		return (NULL);
	line = NULL;
	if (!list)
	{
		list = malloc(sizeof(t_list));
		if (!list)
			return (NULL);
		list->c = '*';
		list->next = NULL;
	}
	head = list;
	rd = read_file(&list, fd);
	if (rd > 0 && list->next)
	{
		list = head;
		line = save_line(&list->next);
	}
	while (list)
	{
		head = list->next;
		free(list);
		list = head;
	}
	return (line);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

// cc -Wall -Wextra -Werror -g ./get_next_line.c -I ./
