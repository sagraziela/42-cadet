/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:27:00 by gde-souz          #+#    #+#             */
/*   Updated: 2023/10/18 13:27:02 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

t_list	*create_node(char c)
{
	t_list	*new_node;

	if (!c)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = c;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstadd(t_list *lst, char *buffer, t_list *head)
{
	t_list	*last;
	int		i;

	i = 0;
	if (head == NULL)
	{
		lst = create_node(buffer[i]);
		head = lst;
		i++;
	}
	while (buffer[i] != '\0')
	{
		while ((lst)->next)
			lst = (lst)->next;
		last = lst;
		last->next = create_node(buffer[i]);
		i++;
	}
	return (head);
}

int	find_line_break(t_list *list)
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

t_list	*dealloc(t_list *head, char *buffer)
{
	t_list	*temp;

	temp = NULL;
	while (head)
	{
		temp = (head)->next;
		free(head);
		head = temp;
	}
	free(buffer);
	return (NULL);
}
