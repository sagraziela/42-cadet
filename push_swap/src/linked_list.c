/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:49:38 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/31 11:52:22 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_tab	*create_new_node(int content)
{
	t_tab	*new_node;

	new_node = (t_tab *)malloc(sizeof(t_tab));
	if (!new_node)
		return (NULL);
	new_node->value = content;
	new_node->index = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	ft_lstadd_node(t_tab **lst, t_tab *new)
{
	t_tab	*temp;
	t_tab	*last;

	last = NULL;
	if ((*lst) == NULL)
		(*lst) = new;
	else
	{
		if ((*lst)->next == NULL)
			last = *lst;
		else
		{
			temp = *lst;
			while (temp->next != NULL)
			{
				last = temp->next;
				temp = temp->next;
			}
		}
		last->next = new;
		new->prev = last;
	}
}

t_tab	*create_list(int *list)
{
	int		i;
	t_tab	*new_node;
	t_tab	*head;

	i = 0;
	head = NULL;
	while (list[i])
	{
		new_node = create_new_node(list[i]);
		ft_lstadd_node(&head, new_node);
		i++;
	}
	ft_printf("%sHEAD = %d%s\n", GREEN, head->value, END);
	return (head);
}
