/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:25:38 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/06 17:06:51 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	print_sorted_list(t_tab *list, int moves)
{
	t_tab	*temp;

	if (list)
	{
		temp = list;
		ft_printf("RESULT =");
		ft_printf(" %d |", list->value);
		list = list->next;
		while (list && list != temp)
		{
			ft_printf(" %d |", list->value);
			list = list->next;
		}
		ft_printf("\n");
		ft_printf("COUNT = %d\n", moves);
	}
}

void	find_edges(t_stack	**stack)
{
	long	highest;
	long	lowest;
	int		count;
	t_tab	*list;

	highest = (*stack)->a_list->value;
	lowest = (*stack)->a_list->value;
	count = 1;
	list = (*stack)->a_list->next;
	while (list != (*stack)->a_list)
	{
		if (list->value > highest)
			highest = list->value;
		if (list->value < lowest)
			lowest = list->value;
		list = list->next;
		count++;
	}
	(*stack)->length = count;
	(*stack)->highest = highest;
	(*stack)->lowest = lowest;
}

void	set_indexes(t_stack **stack)
{
	t_tab	*list;
	t_tab	*next;
	long	lowest;
	int		i;

	lowest = (*stack)->lowest;
	i = 1;
	while (i <= (*stack)->length)
	{
		list = (*stack)->a_list;
		while (list->value != lowest)
			list = list->next;
		list->index = i;
		next = list->next;
		lowest = next->value;
		while (next != list)
		{
			if ((next->value > list->value && next->value < lowest)
				|| (lowest < list->value))
				lowest = next->value;
			next = next->next;
		}
		i++;
	}
}

void	set_positions(t_tab **list)
{
	int		i;
	t_tab	*temp;

	temp = *list;
	(*list)->pos = 0;
	if ((*list)->next != NULL)
		*list = (*list)->next;
	i = 1;
	while (*list && *list != temp)
	{
		(*list)->pos = i;
		*list = (*list)->next;
		i++;
	}
}

void	set_target(t_stack **stack)
{
	int		i;
	t_tab	*temp;

	temp = (*stack)->a_list;
	i = 0;
	while (i++ < get_list_length((*stack)->b_list))
	{
		while ((*stack)->a_list->index > (*stack)->a_list->prev->index)
			(*stack)->a_list = (*stack)->a_list->prev;
		while ((*stack)->a_list->index < (*stack)->b_list->index)
		{
			if ((*stack)->a_list->index == (*stack)->b_list->index + 1
				|| ((*stack)->a_list->prev->index
					== (*stack)->b_list->index - 1)
				|| (*stack)->b_list->index == (*stack)->length)
				break ;
			(*stack)->a_list = (*stack)->a_list->next;
		}
		(*stack)->b_list->target_pos = (*stack)->a_list->pos;
		if ((*stack)->b_list->next)
			(*stack)->b_list = (*stack)->b_list->next;
		else
			break ;
	}
	(*stack)->a_list = temp;
}
