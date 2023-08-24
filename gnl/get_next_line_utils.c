/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:39:10 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/24 19:31:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

t_list	*ft_lstadd(t_list *lst, char content)
{
	t_list	*last;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ((t_list *)0);
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
	while (buffer[i] != '\0' && i < rd)
	{
		node = ft_lstadd(list, buffer[i]);
		i++;
	}
	return (node);
}

int	find_line_break_buffer(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n' || *buffer == '\0')
			return (1);
		buffer++;
	}
	return (0);
}

int	find_line_break_list(t_list *list)
{
	while (list)
	{
		if (list->content == '\n')
			return (1);
		list = list->next;
	}
	return (0);
}

size_t	find_line_len(t_list *list)
{
	size_t	counter;

	counter = 0;
	while (list)
	{
		counter++;
		if (list->content == '\n' || list->content == '\0')
			break ;
		list = list->next;
	}
	return (counter);
}
