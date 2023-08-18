/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:38:30 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/18 18:29:19 by gde-souz         ###   ########.fr       */
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
		while ((*list)->content[j] != '\0' && i < line_len)
		{
			line[i] = (*list)->content[j];
			i++;
			j++;
		}
		*list = (*list)->next;
		j = 0;
	}
	line[i] = '\0';
	return (line);
}

static int	increment_list(t_list **list, char *buffer)
{
	char	*line_break;
	int		line_len;

	line_len = 17;
	line_break = ft_strchr((*list)->content, '\n');
	ft_lstadd(list, buffer);
	if (line_break)
	{
		while (list)
		{
			printf("%s\n", (*list)->content);
			printf("END NODE\n");
			*list = (*list)->next;
		}
	}
	printf("%d\n", line_len);
	return (line_len);
}

char	*get_next_line(int fd)
{
	static t_list	**list;
	char			buffer[BUFF_SIZE + 1];
	char			*line;
	int				line_len;
	int				rd;

	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	if (!list)
		list = (t_list **)malloc(sizeof(t_list **));
	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFF_SIZE);
		buffer[BUFF_SIZE] = '\0';
		if (rd == -1)
			return (0);
		line_len = increment_list(list, buffer);
	}
	line = join_buffers(list, line_len);
	return (line);
}

int	main(void)
{
	int		file;
	char	*line;

	file = open("../file.txt", O_RDONLY);
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
//cc get_next_line.c get_next_line_utils.c get_next_line.h