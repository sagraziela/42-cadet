/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:10:00 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/14 16:08:05 by root             ###   ########.fr       */
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

void	ft_lstadd(t_list **lst, void *content)
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

t_list	**create_list(t_list **list, int fd)
{
	char			*first_buffer;
	char			*buffer;
	size_t			rd;

	if (fd < 0 || BUFF_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	rd = 1;
	while (rd > 0)
	{
		buffer = malloc(BUFF_SIZE + 1);
		if (!buffer)
			return (NULL);
		rd = read(fd, buffer, BUFF_SIZE);
		buffer[rd] = '\0';
		ft_lstadd(list, buffer);
	}
	return (list);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (s[length] != '\0')
		length++;
	if ((unsigned char) c == '\0')
	{
		return ((char *)s + length);
	}
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

void	find_next_line(t_list *list)
{
	int	i;
	int	bf;

	i = 0;
	while (list != NULL)
	{
		while (i < BUFF_SIZE)
		{
			if (list->content[i] == '\n')
			{
				printf("\nEND\n");
				return ;
			}
			printf("%c", list->content[i]);
			i++;
		}
		i = 0;
		list = list->next;
	}
}

char	*get_next_line(int fd)
{
	static t_list	**list;
	char			*buff;
	int				i;

	i = 0;
	list = malloc(0);
	list = create_list(list, fd);
	find_next_line(*list);
	return ((*list)->content);
}

int	main(void)
{
	int	file;

	file = open("file.txt", O_RDONLY);
	get_next_line(file);
	close(file);
}

//cc get_next_line.c get_next_line_utils.c get_next_line.h