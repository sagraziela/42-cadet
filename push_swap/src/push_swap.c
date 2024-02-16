/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/16 19:20:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	print_sorted_list(t_tab *list, int len)
{
	int		i;

	i = 0;
	ft_printf("RESULT =");
	while (i < len)
	{
		ft_printf(" %d |", list->value);
		list = list->next;
		i++;
	}
	ft_printf("\n");
}

void	sort_three(t_stack **stack)
{
	if ((*stack)->a_list->value > (*stack)->a_list->next->value
		&& (*stack)->a_list->value > (*stack)->a_list->prev->value)
		ra(&(*stack)->a_list);
	if ((*stack)->a_list->prev->value < (*stack)->a_list->next->value)
		rra(&(*stack)->a_list);
	if ((*stack)->a_list->value > (*stack)->a_list->next->value)
		sa(&(*stack)->a_list);
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
		{
			list = list->next;
		}
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

void	sort(t_stack **stack)
{
	int		i;
	int		mid;
	int		max;

	i = 0;
	mid = (*stack)->length / 2;
	max = (*stack)->length - 2;
	if ((*stack)->length % 2 != 0)
	{
		mid++;
		max++;
	}
	while (i < (*stack)->length)
	{
		if ((*stack)->a_list->index < mid)
			pb(&(*stack)->a_list, &(*stack)->b_list);
		else
			(*stack)->a_list = (*stack)->a_list->next;
		i++;
	}
	while (i > mid)
	{
		if ((*stack)->a_list->index < max)
			pb(&(*stack)->a_list, &(*stack)->b_list);
		else
			(*stack)->a_list = (*stack)->a_list->next;
		i--;
	}
	sort_three(&(*stack));
	print_sorted_list((*stack)->a_list, 3);
	print_sorted_list((*stack)->b_list, (*stack)->length - 3);
	ft_printf("\n");
	while ((*stack)->b_list)
	{
		if ((*stack)->a_list->index == (*stack)->b_list->index - 1)
		{
			pa(&(*stack)->a_list, &(*stack)->b_list);
			sa(&(*stack)->a_list);
		}
		else if (((*stack)->a_list->index == (*stack)->b_list->index + 1)
			|| ((*stack)->a_list->prev->index + 1 == (*stack)->b_list->index))
		{
			pa(&(*stack)->a_list, &(*stack)->b_list);
		}
		else if (((*stack)->b_list->prev)
			&& ((*stack)->b_list->prev->index + 1 == (*stack)->a_list->index))
		{
			rrb(&(*stack)->b_list);
			pa(&(*stack)->a_list, &(*stack)->b_list);
		}
		else if (((*stack)->b_list->next)
			&& ((*stack)->b_list->next->index + 1 == (*stack)->a_list->index))
		{
			rb(&(*stack)->b_list);
			pa(&(*stack)->a_list, &(*stack)->b_list);
		}
		else
		{
			if (((*stack)->b_list->index - (*stack)->a_list->index)
				> ((*stack)->b_list->index - (*stack)->a_list->prev->index))
			{
				while ((*stack)->a_list->index < (*stack)->b_list->index)
				{
					//ft_printf("1º WHILE\n");
					ra(&(*stack)->a_list);
					//print_sorted_list((*stack)->a_list, (*stack)->length);
				}
			}
			else
			{
				while ((*stack)->a_list->index < (*stack)->b_list->index)
				{
					//ft_printf("2º WHILE\n");
					rra(&(*stack)->a_list);
				}
			}
			pa(&(*stack)->a_list, &(*stack)->b_list);
		}
	}
	if ((*stack)->a_list->index > ((*stack)->length / 2))
	{
		while ((*stack)->a_list->index != 1)
			ra(&(*stack)->a_list);
	}
	else
		while ((*stack)->a_list->index != 1)
			rra(&(*stack)->a_list);
	print_sorted_list((*stack)->a_list, (*stack)->length);
}

void	push_swap(t_stack *stack)
{
	t_tab	*list;

	list = stack->a_list;
	if (stack->length == 2)
	{
		if (list->value > list->next->value)
			sa(&stack->a_list);
		else
			ft_printf("%sOK\n%s", GREEN, END);
	}
	else if (stack->length == 3)
	{
		sort_three(&stack);
		print_sorted_list(stack->a_list, stack->length);
	}
	else
	{
		ft_printf("%sDEVELOPING...%s\n", YELLOW, END);
		find_edges(&stack);
		set_indexes(&stack);
		sort(&stack);
	}
}
