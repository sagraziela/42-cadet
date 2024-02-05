/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:07:19 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/05 18:29:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	pa(t_tab **a_list, t_tab **b_list)
{
	t_tab	*temp_b;
	t_tab	*temp_b_prev;
	t_tab	*temp_a_prev;

	if (!(*b_list))
		return ;
	temp_b = *b_list;
	if (!(*b_list)->next)
		*b_list = NULL;
	else
	{
		temp_b_prev = (*b_list)->prev;
		*b_list = (*b_list)->next;
		if (temp_b_prev == *b_list)
		{
			(*b_list)->prev = NULL;
			(*b_list)->next = NULL;
		}
		else
		{
			(*b_list)->prev = temp_b_prev;
			temp_b_prev->next = *b_list;
		}
	}
	temp_a_prev = (*a_list)->prev;
	temp_a_prev->next = temp_b;
	temp_b->next = *a_list;
	temp_b->prev = temp_a_prev;
	(*a_list)->prev = temp_b;
	*a_list = temp_b;
	ft_printf("%spa\n%s", BLUE, END);
	return ;
}

void	pb(t_tab **a_list, t_tab **b_list)
{
	t_tab	*temp_b_prev;
	t_tab	*temp_a_prev;
	t_tab	*temp_b;

	temp_b = *a_list;
	temp_a_prev = (*a_list)->prev;
	*a_list = (*a_list)->next;
	temp_a_prev->next = *a_list;
	(*a_list)->prev = temp_a_prev;
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
