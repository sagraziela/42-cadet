/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:29 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/19 18:13:42 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./gnl.h"

char	*save_line(t_list **list)
{
	int		i;
	int		n;
	char	*line;
	t_list	*temp;

	i = 0;
	while ((*list)->c != '\n')
	{
		n++;
		*list = (*list)->next;
	}
	line = malloc(sizeof(char) * (n + 2));
	if (!line)
		return (NULL);
	n++;
	while (i < n)
	{
		line[i] = (*list)->c;
		temp = (*list)->next;
		free(*list);
		*list = temp;
		i++;
	}
	line[n] = '\0';
	//printf("%s\n", line);
	return (line);
}

void	fill_list(t_list **list, char *buffer)
{
	int		i;
	t_list	*head;
	t_list	*new;

	i = 0;
	if (*list)
		head = *list;
	else
		head = NULL;
	while ((*list)->next)
		*list = (*list)->next;
	while (buffer[i] != '\0')
	{
		new = malloc(sizeof(t_list));
		if (!(*list))
			return ;
		new->c = buffer[i];
		new->next = NULL;
		(*list)->next = new;
		//printf("%c", (*list)->c);
		*list = (*list)->next;
		i++;
	}
	if (head)
		*list = head;
}

t_list	*read_file(int fd, t_list **list)
{
	int		rd;
	int		i;
	char	*buffer;

	rd = 1;
	i = 0;
	while (rd > 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			printf("VIXE: Deu ruim no read()\n");
			free(buffer);
			return (NULL);
		}
		else
		{
			fill_list(list, buffer);
			printf("%c\n", (*list)->c);
			while (buffer[i])
			{
				if (buffer[i] == '\n')
				{
					free(buffer);
					return (*list);
				}
				i++;
			}
		}
		free(buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			**head;
	char			*line;
	int				i;
	int				rd;
	
	i = 0;
	if (!list)
	{
		list = malloc(sizeof(t_list));
		list->c = '^';
		list->next = NULL;
	}
	head = &list;
	list = read_file(fd, &list);
	list = *head;
	printf("%c\n", list->c);
	line = save_line(&list);
	return (line);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

	if(argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd > 0)
	{
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			//printf("%s\n", line);
			free(line);
		}
		close(fd);
		return (0);
	}
	printf("Failed to open FD\n");
	return (1);
}
