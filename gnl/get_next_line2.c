/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:40:06 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/17 16:39:38 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_buffers(t_list **list, int line_len)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = (char *)malloc((line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < line_len)
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
	return (line);
}

static int	increment_list(t_list **list, char *buffer)
{
	int		line_break;
	int		i;
	int		line_len;

	i = 0;
	line_len = 0;
	line_break = find_line_break(buffer);
	ft_lstadd(list, buffer);
	if (line_break)
	{
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
	}
	printf("%d\n", line_len);
	return (line_len);
}

static int	fill_buffer(t_list **list, int fd, char *buffer)
{
	int		rd;
	int		line_len;

	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFF_SIZE);
		buffer[BUFF_SIZE] = '\0';
		if (!rd)
			return (0);
		line_len = increment_list(list, buffer);
	}
	return (line_len);
}

char	*get_next_line(int fd)
{
	static t_list	**list;
	char			buffer[BUFF_SIZE + 1];
	char			*line;
	int				line_len;

	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!list)
	{
		list = (t_list **)malloc(sizeof(t_list **));
	}
	line_len = fill_buffer(list, fd, buffer);
	line = join_buffers(list, line_len);
	return (line);
}

int	main(void)
{
	int	file;

	file = open("file.txt", O_RDONLY);
	get_next_line(file);
	close(file);
}
//cc get_next_line2.c get_next_line_utils.c get_next_line.h
