/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:09:13 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/16 12:04:01 by root             ###   ########.fr       */
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

	if (!(*list) || !(*list)->next)
		return ;
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
	ft_printf("%ssb\n%s", CYAN, END);
	return ;
}

void	ss(t_tab **a_list, t_tab **b_list)
{
	t_tab	*a_temp;
	t_tab	*b_temp;
	t_tab	*a_next;
	t_tab	*b_next;

	if (!(*a_list) || !(*a_list)->next || !(*b_list) || !(*b_list)->next)
		return ;
	a_temp = *a_list;
	a_next = a_temp->next;
	a_next->prev = a_temp;
	(*a_list) = (*a_list)->next;
	a_temp->next = (*a_list)->next;
	(*a_list)->next = a_temp;
	(*a_list)->prev = a_temp->prev;
	a_temp->prev = (*a_list);
	b_temp = *b_list;
	b_next = b_temp->next;
	b_next->prev = b_temp;
	(*b_list) = (*b_list)->next;
	b_temp->next = (*b_list)->next;
	(*b_list)->next = b_temp;
	(*b_list)->prev = b_temp->prev;
	b_temp->prev = (*b_list);
	ft_printf("%sss\n%s", BLUE, END);
	return ;
}
