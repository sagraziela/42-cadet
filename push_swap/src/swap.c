/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:09:13 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/21 18:36:28 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_tab **list)
{
	t_tab	*temp;
	t_tab	*prev;
	t_tab	*next;

	temp = *list;
	prev = (*list)->prev;
	*list = (*list)->next;
	temp->next = (*list)->next;
	next = temp->next;
	(*list)->next = temp;
	(*list)->prev = prev;
	prev->next = *list;
	temp->prev = *list;
	next->prev = temp;
	ft_printf("%ssa\n%s", CYAN, END);
	return ;
}

void	sb(t_tab **list)
{
	t_tab	*temp;
	t_tab	*prev;
	t_tab	*next;

	temp = *list;
	*list = (*list)->next;
	if (temp->next == temp->prev)
		return ;
	else
	{
		prev = temp->prev;
		next = (*list)->next;
		temp->next = (*list)->next;
		(*list)->next = temp;
		(*list)->prev = prev;
		prev->next = *list;
		temp->prev = *list;
		next->prev = temp;
	}
	ft_printf("%ssb\n%s", CYAN, END);
	return ;
}

void	ss(t_tab **a_list, t_tab **b_list)
{
	t_tab	*temp;
	t_tab	*a_next;
	t_tab	*b_next;
	t_tab	*b_prev;

	temp = *a_list;
	a_next = temp->next;
	a_next->prev = temp;
	(*a_list) = (*a_list)->next;
	temp->next = (*a_list)->next;
	(*a_list)->next = temp;
	(*a_list)->prev = temp->prev;
	temp->prev = (*a_list);
	temp = *b_list;
	*b_list = (*b_list)->next;
	if (temp->next == temp->prev)
		return ;
	else
	{
		b_prev = temp->prev;
		b_next = (*b_list)->next;
		temp->next = (*b_list)->next;
		(*b_list)->next = temp;
		(*b_list)->prev = b_prev;
		b_prev->next = *b_list;
		temp->prev = *b_list;
		b_next->prev = temp;
	}
	ft_printf("%sss\n%s", BLUE, END);
	return ;
}
