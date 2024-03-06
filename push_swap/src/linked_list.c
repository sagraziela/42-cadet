/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:49:38 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/06 12:45:29 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_tab	*create_new_node(int content)
{
	t_tab	*new_node;

	new_node = (t_tab *)ft_calloc(1, sizeof(t_tab));
	if (!new_node)
		return (NULL);
	new_node->value = content;
	return (new_node);
}

void	ft_lstadd_node(t_tab **head, t_tab *new)
{
	t_tab	*temp;
	t_tab	*last;

	last = NULL;
	if ((*head) == NULL)
		(*head) = new;
	else
	{
		if ((*head)->next == NULL)
			last = *head;
		else
		{
			temp = *head;
			while (temp->next != *head)
			{
				last = temp->next;
				temp = temp->next;
			}
		}
		last->next = new;
		new->prev = last;
		new->next = *head;
		(*head)->prev = new;
	}
}

t_tab	*create_list(int *list, int len)
{
	int		i;
	t_tab	*new_node;
	t_tab	*head;

	i = 0;
	head = NULL;
	while (i < len)
	{
		new_node = create_new_node(list[i]);
		ft_lstadd_node(&head, new_node);
		i++;
	}
	return (head);
}

int	get_list_length(t_tab *list)
{
	int		count;
	t_tab	*temp;

	if (list == NULL)
		return (0);
	temp = list;
	count = 1;
	if (list->next)
		list = list->next;
	else
		return (count);
	while (list->index != temp->index)
	{
		count++;
		list = list->next;
	}
	return (count);
}
