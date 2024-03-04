/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:25:38 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/04 17:48:13 by gde-souz         ###   ########.fr       */
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

void	set_cost_a(t_stack ***stack)
{
	int		i;
	t_tab	*temp;

	i = 0;
	while (i < get_list_length((**stack)->a_list))
	{
		(**stack)->a_list->cost_a = 0;
		temp = (**stack)->a_list;
		while (temp->pos != 0)
		{
			if (get_list_length(temp) / 2 < (**stack)->a_list->pos)
			{
				(**stack)->a_list->cost_a--;
				temp = temp->next;
			}
			else
			{
				(**stack)->a_list->cost_a++;
				temp = temp->prev;
			}
		}
		//ft_printf("A = %d | cost_a = %d\n", (**stack)->a_list->value, (**stack)->a_list->cost_a);
		(**stack)->a_list = (**stack)->a_list->next;
		i++;
	}
}

void	set_cost_b(t_stack ***stack)
{
	int		i;
	t_tab	*temp;

	i = 0;
	while (i < get_list_length((**stack)->b_list))
	{
		(**stack)->b_list->cost_b = 0;
		temp = (**stack)->b_list;
		while (temp->pos != 0)
		{
			if (get_list_length(temp) / 2 < (**stack)->b_list->pos)
			{
				(**stack)->b_list->cost_b--;
				temp = temp->next;
			}
			else
			{
				(**stack)->b_list->cost_b++;
				temp = temp->prev;
			}
		}
		//ft_printf("B = %d | pos_b = %d cost_b = %d\n", (**stack)->b_list->value, (**stack)->b_list->pos, (**stack)->b_list->cost_b);
		if ((**stack)->b_list->next)
			(**stack)->b_list = (**stack)->b_list->next;
		i++;
	}
}

void	set_full_cost(t_stack ***stack)
{
	int					i;
	t_tab				*temp_a;
	t_tab				*temp_b;

	i = 0;
	temp_a = (**stack)->a_list;
	temp_b = (**stack)->b_list;
	while (i < get_list_length((**stack)->b_list))
	{
		while ((**stack)->a_list->pos != (**stack)->b_list->target_pos)
		{
			ft_printf("A = %d\n", (**stack)->a_list->value);
			(**stack)->a_list = (**stack)->a_list->next;
		}
		//ft_printf("A = %d		|	B = %d\ncost_a = %d	|	cost_b = %d\n\n", (**stack)->a_list->value, (**stack)->b_list->value, (**stack)->a_list->cost_a, (**stack)->b_list->cost_b);
		(**stack)->b_list->cost_a = (**stack)->a_list->cost_a;
		if ((**stack)->a_list->cost_a < 0)
			(**stack)->a_list->cost_a *= -1;
		if ((**stack)->b_list->cost_b < 0)
			(**stack)->a_list->cost_b = (**stack)->b_list->cost_b * (-1);
		else
			(**stack)->a_list->cost_b = (**stack)->b_list->cost_b;
		(**stack)->b_list->cost = (**stack)->a_list->cost_a + (**stack)->a_list->cost_b;
		//ft_printf("%d -- pos: %d -- target: %d\n", (**stack)->b_list->value, (**stack)->b_list->pos, (**stack)->b_list->target_pos);
		//ft_printf("value: %d | cost: %d | cost_a: %d | cost_b: %d\n", (**stack)->b_list->value, (**stack)->b_list->cost, (**stack)->a_list->cost_a, (**stack)->b_list->cost_b);
		(**stack)->b_list = (**stack)->b_list->next;
		i++;
	}
	(**stack)->a_list = temp_a;
	(**stack)->b_list = temp_b;
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
