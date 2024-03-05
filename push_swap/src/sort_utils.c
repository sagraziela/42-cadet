/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:25:38 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/05 16:47:30 by root             ###   ########.fr       */
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
	print_sorted_list((*stack)->a_list, (*stack)->moves);
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

void	set_target(t_stack ***stack)
{
	int		i;
	t_tab	*temp;

	temp = (**stack)->a_list;
	i = 0;
	while ((**stack)->b_list && i < get_list_length((**stack)->b_list))
	{
		while ((**stack)->a_list->index > (**stack)->a_list->prev->index)
			(**stack)->a_list = (**stack)->a_list->prev;
		while ((**stack)->a_list->index < (**stack)->b_list->index)
		{
			//ft_printf("A = %d | a_pos: %d\n", (**stack)->a_list->value, (**stack)->a_list->pos);
			if ((**stack)->a_list->index == (**stack)->b_list->index + 1)
				break ;
			(**stack)->a_list = (**stack)->a_list->next;
		}
		(**stack)->b_list->target_pos = (**stack)->a_list->pos;
		// ft_printf("B = %d | target = %d | A = %d | a_pos: %d\n", (**stack)->b_list->value, (**stack)->b_list->target_pos, (**stack)->a_list->value, (**stack)->a_list->pos);
		if ((**stack)->b_list->next)
			(**stack)->b_list = (**stack)->b_list->next;
		else
			break ;
		i++;
	}
	(**stack)->a_list = temp;
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
