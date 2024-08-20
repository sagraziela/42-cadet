/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:29 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/20 15:49:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./gnl.h"

char	*save_line(t_list **list)
{
	t_list	*temp;
	char	*line;
	int		n;
	int		i;

	n = 0;
	temp = *list;
	while ((*list))
	{
		if ((*list)->c == '\0' || (*list)->c == '\n')
			break ;
		n++;
		*list = (*list)->next;
	}
	n++;
	*list = temp;
	line = malloc(sizeof(char) * (n + 1));
	if (!line)
		return (NULL);
	i = 0;
	printf("n = %d\n", n);
	while (i < n && (*list))
	{
		// printf("list: %c\n", (*list)->c);
		line[i] = (*list)->c;
		temp = (*list)->next;
		free(*list);
		*list = temp;
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	read_file(int fd, t_list **list)
{
	int		rd;
	int		i;
	char	*buffer;
	t_list	*head;
	t_list	*new;

	rd = 1;
	while (rd > 0)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (-1);
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == 0 || rd == -1)
			break ;
		else
		{
			buffer[rd] = '\0';
			i = 0;
			head = *list;
			while ((*list)->next)
				*list = (*list)->next;
			while (i < rd)
			{
				new = malloc(sizeof(t_list));
				if (!new)
					return (-1);
				new->c = buffer[i];
				new->next = NULL;
				(*list)->next = new;
				*list = (*list)->next;
				i++;
			}
			*list = head;
			i = 0;
			while (buffer[i])
			{
				if (buffer[i] == '\n' || buffer[i] == '\0')
				{
					free(buffer);
					return (fd);
				}
				i++;
			}
		}
		free(buffer);
	}
	if (buffer)
		free(buffer);
	return (rd);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*head;
	t_list			*temp;
	int				ret;
	char			*line;
	
	if (!list)
	{
		list = malloc(sizeof(t_list));
		list->c = '^';
		list->next = NULL;
	}
	head = list;
	ret = read_file(fd, &list);
	list = head;
	line = NULL;
	if (ret >= 0 && list->next)
	{
		line = save_line(&list->next);
	}
	list = head;
	if (ret <= 0)
	{
		while (list)
		{
			temp = (list)->next;
			free(list);
			list = temp;
		}
		if (!line)
			return (NULL);
	}
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
			printf("%s", line);
			free(line);
		}
		close(fd);
		return (0);
	}
	printf("Failed to open FD\n");
	return (1);
}


// cc -Wall -Wextra -Werror -g ./gnl.c -I./
// valgrind --leak-check=full --track-origins=yes ./a.out ./test.txt
