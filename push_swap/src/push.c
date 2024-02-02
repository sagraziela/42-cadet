/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:07:19 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/02 13:20:35 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	pa(t_tab **a_list, t_tab **b_list)
{
	t_tab	*temp_b;

	if (!(*b_list))
		return ;
	temp_b = *b_list;
	if ((*b_list)->prev == (*b_list)->next) //only 2 nodes exists
	{
		(*b_list)->next = NULL;
		(*b_list)->prev = NULL;
	}
	else
	{
		temp_b->prev = (*b_list)->prev;
		(*b_list)->prev->next = temp_b;
		(*b_list)->next = (*a_list);
		(*b_list)->prev = (*a_list)->prev;
		(*a_list)->prev = *b_list;
		*a_list = (*a_list)->prev;
		*b_list = temp_b;
	}
	ft_printf("%spa\n%s", BLUE, END);
	return ;
}

void	pb(t_tab **a_list, t_tab **b_list)
{
	t_tab	*temp_a_prev;
	t_tab	*temp_b;

	temp_a_prev = (*a_list)->prev;
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
		(*b_list)->prev = temp_b;
		temp_b->next = *b_list;
		*b_list = (*b_list)->prev;
	}
	ft_printf("%spb\n%s", BLUE, END);
	return ;
}
