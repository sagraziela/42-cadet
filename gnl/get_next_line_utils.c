/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:39:10 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/28 17:50:03 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_malloc(size_t size)
{
	char	*memory;

	memory = (void *)malloc(size);
	if (!memory)
		return (NULL);
	return (memory);
}

t_list	*ft_lstadd(t_list *lst, char content)
{
	t_list	*last;
	t_list	*new_node;

	if (!content)
		return (lst);
	new_node = (t_list *)ft_malloc(sizeof(t_list));
	new_node->content = content;
	new_node->next = NULL;
	if (lst == NULL)
		lst = new_node;
	else
	{
		while (lst->next)
			lst = lst->next;
		last = lst;
		last->next = new_node;
	}
	return (lst);
}

t_list	*create_nodes(t_list *list, char *buffer, int rd)
{
	int		i;
	t_list	*node;

	i = 0;
	node = NULL;
	while (buffer[i] != '\0' && i < rd)
	{
		node = ft_lstadd(list, buffer[i]);
		i++;
	}
	return (node);
}

int	find_line_break_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

size_t	find_line_break_list(t_list *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		if (list->content == '\n' || list->content == '\0')
			return (i);
		list = list->next;
	}
	return (0);
}
