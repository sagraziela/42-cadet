/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:09:13 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/06 12:48:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_tab **list)
{
	t_tab	*temp;

	temp = *list;
	*list = (*list)->next;
	temp->next = (*list)->next;
	(*list)->next = temp;
	(*list)->prev = temp->prev;
	temp->prev = *list;
	ft_printf("%ssa\n%s", CYAN, END);
	return ;
}

void	sb(t_tab **list)
{
	t_tab	*temp;

	if (!(*list) || !(*list)->next)
		return ;
	temp = *list;
	*list = (*list)->next;
	temp->next = (*list)->next;
	(*list)->next = temp;
	(*list)->prev = temp->prev;
	temp->prev = *list;
	ft_printf("%ssb\n%s", CYAN, END);
	return ;
}

void	ss(t_tab **a_list, t_tab **b_list)
{
	t_tab	*a_temp;
	t_tab	*b_temp;

	if (!(*a_list) || !(*a_list)->next || !(*b_list) || !(*b_list)->next)
		return ;
	a_temp = *a_list;
	(*a_list) = (*a_list)->next;
	a_temp->next = (*a_list)->next;
	(*a_list)->next = a_temp;
	(*a_list)->prev = a_temp->prev;
	a_temp->prev = (*a_list);
	b_temp = *b_list;
	(*b_list) = (*b_list)->next;
	b_temp->next = (*b_list)->next;
	(*b_list)->next = b_temp;
	(*b_list)->prev = b_temp->prev;
	b_temp->prev = (*b_list);
	ft_printf("%sss\n%s", BLUE, END);
	return ;
}
