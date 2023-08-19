/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:40:48 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/19 18:18:49 by gde-souz         ###   ########.fr       */
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

	i = 0;
	j = 0;
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

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if ((unsigned char) c == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

void	ft_lstadd(t_list **lst, char content)
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
		while ((*lst)->next != NULL)
			*lst = (*lst)->next;
		last = *lst;
		last->next = new_node;
	}
}

static size_t	create_nodes(t_list **list, char *buffer)
{
	size_t	i;
	size_t	counter;

	i = 0;
	while (buffer[i] != '\0')
	{
		ft_lstadd(list, buffer[i]);
		i++;
	}
	counter = 0;
	if (ft_strchr(buffer, '\n'))
	{
		counter = 1;
		// PRECISA CONTAR A QNTD DE LETRAS DA LINHA NUMA FUNÇÃO À PARTE!
	}
	free(buffer);
	return (counter);
}

static void	find_line_break(t_list *list, char *line)
{
	size_t	i;
	t_list	*next_node;

	i = 0;
	while (list)
	{
		//printf("%c", list->content);
		line[i] = list->content;
		next_node = list->next;
		free(list);
		list = next_node;
		if (list->content == '\n')
			break ;
	}
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
	rd = 1;
	line_len = 0;
	while (rd > 0 && line_len == 0)
	{
		read(fd, buffer, BUFF_SIZE);
		line_len = create_nodes(list, buffer);
	}
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	find_line_break(*list, line);
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

//cc get_next_line2.c get_next_line.h
