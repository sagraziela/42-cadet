/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/06 18:56:40 by root             ###   ########.fr       */
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
	ft_printf("Highest = %d | Lowest = %d\n", (*stack)->highest, (*stack)->lowest);
}

void	set_indexes(t_stack **stack)
{
	t_tab	*list;
	int		i;

	list = (*stack)->a_list;
	i = 0;
	while(i < (*stack)->length)
	{
		if (list->value == (*stack)->highest)
			list->index = (*stack)->length;
		if (list->value == (*stack)->lowest)
			list->index = 1;
		list = list->next;
		i++;
	}
}

void	sort(t_stack **stack)
{
	int		i;

	i = 0;
	while (i < (*stack)->length - 3)
	{
		pb(&(*stack)->a_list, &(*stack)->b_list);
		i++;
	}
	print_sorted_list((*stack)->a_list, 3);
	print_sorted_list((*stack)->b_list, 3);
	ft_printf("\n");
	while (i > 0)
	{
		pa(&(*stack)->a_list, &(*stack)->b_list);
		i--;
	}
	print_sorted_list((*stack)->a_list, 6);
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
