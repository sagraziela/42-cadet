/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:07:19 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/02 17:59:55 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	pa(t_tab **a_list, t_tab **b_list)
{
	t_tab	*temp_b;
	t_tab	*temp_b_prev;
	t_tab	*temp_a_prev;

	//REVISAR!!!
	if (!(*b_list))
		return ;
	temp_b = *b_list;
	ft_printf("temp_a = %d | prev = %d | next = %d\n", (*a_list)->value, (*a_list)->prev->value, (*a_list)->next->value);
	if ((*b_list)->next)
		*b_list = (*b_list)->next;
	if (temp_b == (*b_list)->next)
	{
		(*b_list)->next = NULL;
		(*b_list)->prev = NULL;
	}
	else if (temp_b->next != NULL)
	{
		temp_b_prev = temp_b->prev;
		temp_b_prev->next = (*b_list);
		(*b_list)->prev = temp_b_prev;
	}
	ft_printf("b_list.value = %d\n", temp_b->value);
	temp_a_prev = (*a_list)->prev;
	temp_a_prev->next = temp_b;
	temp_b->next = *a_list;
	temp_b->prev = temp_a_prev;
	(*a_list)->prev = temp_b;
	*a_list = (*a_list)->prev;
	ft_printf("%spa\n%s", BLUE, END);
	return ;
}

void	pb(t_tab **a_list, t_tab **b_list)
{
	t_tab	*temp_b_prev;
	t_tab	*temp_b;

	temp_b = *a_list;
	*a_list = (*a_list)->next;
	if (!(*b_list))
	{
		*b_list = temp_b;
		(*b_list)->next = NULL;
		(*b_list)->prev = NULL;
	}
	else
	{
		if ((*b_list)->next)
			temp_b_prev = (*b_list)->prev;
		else
			temp_b_prev = *b_list;
		(*b_list)->prev = temp_b;
		temp_b_prev->next = temp_b;
		temp_b->next = *b_list;
		temp_b->prev = temp_b_prev;
		*b_list = (*b_list)->prev;
	}
	ft_printf("%spb\n%s", BLUE, END);
	return ;
}
