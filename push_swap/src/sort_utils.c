/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:25:38 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/27 11:59:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	print_sorted_list(t_tab *list, int moves)
{
	t_tab	*temp;

	temp = list;
	ft_printf("RESULT =");
	ft_printf(" %d |", list->value);
	list = list->next;
	while (list != temp)
	{
		ft_printf(" %d |", list->value);
		list = list->next;
	}
	ft_printf("\n");
	ft_printf("COUNT = %d\n", moves);
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

void	set_positions(t_stack **stack)
{
	int		i;
	t_tab	*temp;

	i = 0;
	(*stack)->a_list->pos = i;
	temp = (*stack)->a_list;
	(*stack)->a_list = (*stack)->a_list->next;
	while ((*stack)->a_list != temp)
	{
		(*stack)->a_list->pos = i;
		(*stack)->a_list = (*stack)->a_list->next;
		ft_printf("value: %d | pos: %d\n", (*stack)->a_list->value, (*stack)->a_list->pos);
		i++;
	}
	i = 0;
	(*stack)->b_list->pos = i;
	temp = (*stack)->b_list;
	(*stack)->b_list = (*stack)->b_list->next;
	while ((*stack)->b_list != temp)
	{
		(*stack)->b_list->pos = i;
		(*stack)->b_list = (*stack)->b_list->next;
		i++;
	}
}

int	get_list_length(t_tab *list)
{
	int		count;
	t_tab	*temp;

	if (list == NULL)
		return (0);
	temp = list;
	count = 1;
	if (list->next)
		list = list->next;
	else
		return (count);
	while (list->index != temp->index)
	{
		count++;
		list = list->next;
	}
	return (count);
}
