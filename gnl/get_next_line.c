/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:10:00 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/14 20:01:49 by root             ###   ########.fr       */
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
		if (!rd)
		{
			free(buffer);
			return (NULL);
		}
		buffer[rd] = '\0';
		ft_lstadd(list, buffer);
	}
	return (list);
}

t_list	*find_next_line(t_list *list)
{
	int	i;
	int	bf;

	i = 0;
	while (list != NULL)
	{
		while (i <= BUFF_SIZE)
		{
			printf("%c", list->content[i]);
			if (list->content[i] == '\n')
				return (list);
			i++;
		}
		i = 0;
		list = list->next;
	}
}

void	update_list(t_list **list)
{
	t_list	*temp;
	t_list	*new_node;
	t_list	*aux_next;
	char	*aux_buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*list != NULL)
	{
		while ((*list)->content[i])
		{
			if ((*list)->content[i] == '\n')
			{
				i++;
				aux_buffer = malloc(BUFF_SIZE - i + 2);
				while ((*list)->content[i])
				{
					aux_buffer[j] = (*list)->content[i + j];
					j++;
				}
				aux_buffer = '\0';
				aux_next = (*list)->next;
				free(*list);
				new_node->content = aux_buffer;
				new_node->next = aux_next;
				return ;
			}
			i++;
		}
		if ((*list)->content[i] == '\0')
		{
			temp = (*list)->next;
			free((*list)->content);
			free(*list);
		}
		*list = temp;
	}
}

char	*get_next_line(int fd)
{
	static t_list	**list;

	if (*list)
	{
		*list = find_next_line(*list);
		update_list(list);
	}
	else {
		list = malloc(0);
		list = create_list(list, fd);
	}
	
	return ((*list)->content);
}

int	main(void)
{
	int	file;

	file = open("file.txt", O_RDONLY);
	get_next_line(file);
	get_next_line(file);
	close(file);
}

//cc get_next_line.c get_next_line_utils.c get_next_line.h