/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:25:38 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/28 14:05:54 by gde-souz         ###   ########.fr       */
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

void	set_positions(t_stack ***stack)
{
	int		i;
	t_tab	*temp_a;
	t_tab	*temp_b;

	temp_a = (**stack)->a_list;
	(**stack)->a_list->pos = 0;
	(**stack)->a_list = (**stack)->a_list->next;
	temp_b = (**stack)->b_list;
	(**stack)->b_list->pos = 0;
	if ((**stack)->b_list->next != NULL)
		(**stack)->b_list = (**stack)->b_list->next;
	i = 1;
	while ((**stack)->a_list != temp_a
		|| (**stack)->b_list != temp_b)
	{
		if ((**stack)->a_list != temp_a)
		{
			(**stack)->a_list->pos = i;
			(**stack)->a_list = (**stack)->a_list->next;
		}
		if ((**stack)->b_list && ((**stack)->b_list != temp_b))
		{
			(**stack)->b_list->pos = i;
			(**stack)->b_list = (**stack)->b_list->next;
		}
		i++;
	}
}

void	set_target(t_stack ***stack)
{
	int		i;
	t_tab	*temp;

	i = 0;
	temp = (**stack)->a_list;
	while (i < get_list_length((**stack)->a_list))
	{
		if (temp->index > (**stack)->a_list->index)
			temp = (**stack)->a_list;
		(**stack)->a_list = (**stack)->a_list->next;
		i++;
	}
	i = 0;
	while ((**stack)->b_list && i < get_list_length((**stack)->b_list))
	{
		while (temp->index <= (**stack)->b_list->index
			&& temp->index < (**stack)->length)
		{
			if (temp->index == (**stack)->b_list->index + 1)
				break ;
			temp = temp->next;
		}
		(**stack)->b_list->target_pos = temp->pos;
		temp = (**stack)->a_list;
		if ((**stack)->b_list->next)
			(**stack)->b_list = (**stack)->b_list->next;
		else
			break ;
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
