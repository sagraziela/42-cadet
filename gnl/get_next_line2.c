/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:40:48 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/18 19:04:06 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	char	*joined;
	int		i;
	int		j;

	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	joined = (char *)malloc(sizeof(char) * (total_len + 1));
	if (joined == NULL)
		return (NULL);
	while (i < total_len)
	{
		if (s1[j])
		{
			joined[i] = s1[j];
			j++;
			i++;
		}
		else
		{
			joined[i] = s2[i - j];
			i++;
		}
	}
	joined[i] = '\0';
	return (joined);
}

static void	create_notes(t_list list, char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			
		}
	}
}

char	*get_next_line(int fd)
{
	static t_list	**list;
	char			*buffer;
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
		buffer = (char *)malloc(BUFF_SIZE + 1);
		if (!buffer)
			return (NULL);
		read(fd, buffer, BUFF_SIZE);
		create_nodes(list, buffer);
	}
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

//cc get_next_line2.c get_next_line.h
