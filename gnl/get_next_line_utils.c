/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:01:10 by root              #+#    #+#             */
/*   Updated: 2023/08/17 16:38:20 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *lst)
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

int	find_line_break(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
//cc get_next_line.c get_next_line_utils.c get_next_line.h
