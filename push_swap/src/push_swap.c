/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/20 14:01:59 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

void	push_to_b(t_stack **stack)
{
	int	i;
	int	max;
	int	mid;
	int	small;

	i = 0;
	mid = ((*stack)->length / 3) * 2;
	max = (*stack)->length - 2;
	if ((*stack)->length % 2 != 0)
		mid++;
	small = mid / 2;
	ft_printf("mid: %d | small: %d\n", mid, small);
	while (i < (*stack)->length)
	{
		if ((*stack)->a_list->index <= mid)
		{
			pb(&(*stack)->a_list, &(*stack)->b_list);
			if ((*stack)->b_list->index <= small && (*stack)->b_list->next)
				rb(&(*stack)->b_list);
		}
		else
			(*stack)->a_list = (*stack)->a_list->next;
		i++;
	}
	small = max / 2;
	while (i >= mid)
	{
		if ((*stack)->a_list->index < max)
			pb(&(*stack)->a_list, &(*stack)->b_list);
		else
			(*stack)->a_list = (*stack)->a_list->next;
		i--;
	}
}

void	sort(t_stack **stack)
{
	while ((*stack)->b_list)
	{
		if ((*stack)->b_list->index < (*stack)->b_list->next->index)
		{
			ft_printf();
			sb(&(*stack)->b_list);
		}
		pa(&(*stack)->a_list, &(*stack)->b_list);
		while ((*stack)->a_list->index > (*stack)->a_list->next->index)
		{
			sa(&(*stack)->a_list);
			if ((*stack)->a_list->next->index - (*stack)->a_list->index > 1)
				ra(&(*stack)->a_list);
			ft_printf("got it");
		}
		// while ((*stack)->a_list->index > (*stack)->a_list->prev->index)
		// 	rra(&(*stack)->a_list);
	}
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
		push_to_b(&stack);
		sort_three(&stack);
		print_sorted_list(stack->a_list, 3);
		print_sorted_list(stack->b_list, stack->length - 3);
		ft_printf("\n");
		sort(&stack);
	}
}

// void	sort(t_stack **stack)
// {
// 	while ((*stack)->b_list)
// 	{
// 		if ((*stack)->a_list->index == (*stack)->b_list->index - 1)
// 		{
// 			pa(&(*stack)->a_list, &(*stack)->b_list);
// 			sa(&(*stack)->a_list);
// 		}
// 		else if (((*stack)->a_list->index == (*stack)->b_list->index + 1)
// 			|| ((*stack)->a_list->prev->index + 1 == (*stack)->b_list->index))
// 		{
// 			pa(&(*stack)->a_list, &(*stack)->b_list);
// 		}
// 		else if (((*stack)->b_list->prev)
// 			&& ((*stack)->b_list->prev->index + 1 == (*stack)->a_list->index))
// 		{
// 			rrb(&(*stack)->b_list);
// 			pa(&(*stack)->a_list, &(*stack)->b_list);
// 		}
// 		else if (((*stack)->b_list->next)
// 			&& ((*stack)->b_list->next->index + 1 == (*stack)->a_list->index))
// 		{
// 			sb(&(*stack)->b_list);
// 			pa(&(*stack)->a_list, &(*stack)->b_list);
// 		}
// 		else
// 		{
// 			if (((*stack)->b_list->index - (*stack)->a_list->index)
// 				> ((*stack)->b_list->index - (*stack)->a_list->prev->index))
// 			{
// 				while ((*stack)->a_list->index < (*stack)->b_list->index)
// 				{
// 					//ft_printf("1º WHILE\n");
// 					ra(&(*stack)->a_list);
// 					//print_sorted_list((*stack)->a_list, (*stack)->length);
// 				}
// 			}
// 			else
// 			{
// 				while ((*stack)->a_list->index < (*stack)->b_list->index)
// 				{
// 					//ft_printf("2º WHILE\n");
// 					rra(&(*stack)->a_list);
// 				}
// 			}
// 			pa(&(*stack)->a_list, &(*stack)->b_list);
// 		}
// 	}
// 	if ((*stack)->a_list->index > ((*stack)->length / 2))
// 	{
// 		while ((*stack)->a_list->index != 1)
// 			ra(&(*stack)->a_list);
// 	}
// 	else
// 	{
// 		while ((*stack)->a_list->index != 1)
// 			rra(&(*stack)->a_list);
// 	}
// 	print_sorted_list((*stack)->a_list, (*stack)->length);
// }