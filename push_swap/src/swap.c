/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:09:13 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/14 17:25:24 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_tab **list)
{
	t_tab	*temp;
	t_tab	*prev;

	// NÃO ESTÁ SETANDO O PREV CORRETAMENTE
	temp = *list;
	prev = (*list)->prev;
	*list = (*list)->next;
	temp->next = (*list)->next;
	ft_printf("prev-prev: %d | prev: %d | list: %d\n", (*list)->prev->prev->value, (*list)->prev->value, (*list)->value);
	ft_printf("temp: %d\n", temp->value);
	ft_printf("prev: %d\n", prev->value);
	(*list)->next = temp;
	(*list)->prev = prev;
	prev->next = *list;
	temp->prev = *list;
	ft_printf("prev-prev: %d | prev: %d | list: %d\n", (*list)->prev->prev->value, (*list)->prev->value, (*list)->value);
	ft_printf("%ssa\n%s", CYAN, END);
	return ;
}

void	sb(t_tab **list)
{
	t_tab	*temp;
	t_tab	*prev;

	if (!(*list) || !(*list)->next)
		return ;
	temp = *list;
	prev = (*list)->prev;
	*list = (*list)->next;
	prev->next = *list;
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
