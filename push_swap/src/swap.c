/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:09:13 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/06 14:29:20 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_tab **list, int *moves)
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
	(*moves)++;
	ft_printf("sa\n");
	return ;
}

void	sb(t_tab **list, int *moves)
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
	(*moves)++;
	ft_printf("sb\n");
	return ;
}

void	aux_swap(t_tab ***b_list, t_tab *temp, t_tab *prev, t_tab *next)
{
	temp->next = (**b_list)->next;
	(**b_list)->next = temp;
	(**b_list)->prev = prev;
	prev->next = **b_list;
	temp->prev = **b_list;
	next->prev = temp;
}

void	ss(t_tab **a_list, t_tab **b_list, int *moves)
{
	t_tab	*temp;
	t_tab	*next;
	t_tab	*prev;

	temp = *a_list;
	prev = (*a_list)->prev;
	*a_list = (*a_list)->next;
	temp->next = (*a_list)->next;
	next = temp->next;
	(*a_list)->next = temp;
	(*a_list)->prev = prev;
	prev->next = *a_list;
	temp->prev = *a_list;
	next->prev = temp;
	temp = *b_list;
	*b_list = (*b_list)->next;
	if (temp->next == temp->prev)
		return ;
	else
		aux_swap(&b_list, temp, temp->prev, (*b_list)->next);
	(*moves)++;
	ft_printf("ss\n");
	return ;
}
