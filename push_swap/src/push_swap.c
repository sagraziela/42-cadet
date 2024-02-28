/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/27 20:48:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_three(t_stack **stack)
{
	if ((*stack)->a_list->value > (*stack)->a_list->next->value
		&& (*stack)->a_list->value > (*stack)->a_list->prev->value)
	{
		ra(&(*stack)->a_list, &(*stack)->moves);
	}
	if ((*stack)->a_list->prev->value < (*stack)->a_list->next->value)
	{
		rra(&(*stack)->a_list, &(*stack)->moves);
	}
	if ((*stack)->a_list->value > (*stack)->a_list->next->value)
	{
		sa(&(*stack)->a_list, &(*stack)->moves);
	}
}

void	push_to_b(t_stack **stack)
{
	int	i;
	int	a_len;

	a_len = (*stack)->length;
	(*stack)->mid = a_len / 2;
	while (a_len > 3)
	{
		i = 0;
		(*stack)->small = (*stack)->mid / 2;
		while (i < a_len && get_list_length((*stack)->a_list) > 3)
		{
			if ((*stack)->a_list->index >= (*stack)->mid)
				ra(&(*stack)->a_list, &(*stack)->moves);
			else
			{
				pb(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
				if ((*stack)->b_list->next
					&& (*stack)->b_list->index < (*stack)->small)
					rb(&(*stack)->b_list, &(*stack)->moves);
			}
			i++;
		}
		print_sorted_list((*stack)->b_list, (*stack)->moves);
		a_len = get_list_length((*stack)->a_list);
		ft_printf("MID: %d\n", (*stack)->mid);
		(*stack)->mid = (*stack)->length - (a_len / 2);
	}
}

int	a_and_b_must_swap(t_tab *a_list, t_tab *b_list)
{
	if ((b_list->next)
		&& (a_list->index > a_list->next->index)
		&& (b_list->index < b_list->next->index))
		return (1);
	return (0);
}

void	sort(t_stack **stack)
{
	while ((*stack)->b_list)
	{
		pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
		while ((*stack)->a_list->prev->index != (*stack)->length
			&& ((*stack)->a_list->index < (*stack)->a_list->prev->index))
		{
			rra(&(*stack)->a_list, &(*stack)->moves);
			sa(&(*stack)->a_list, &(*stack)->moves);
			if ((*stack)->b_list
				&& (*stack)->b_list->index > (*stack)->a_list->prev->index
				&& (*stack)->b_list->index < (*stack)->a_list->index)
				pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
		}
		while ((*stack)->a_list->index > (*stack)->a_list->next->index)
		{
			sa(&(*stack)->a_list, &(*stack)->moves);
			ra(&(*stack)->a_list, &(*stack)->moves);
			if ((*stack)->b_list
				&& (*stack)->b_list->index > (*stack)->a_list->prev->index
				&& (*stack)->b_list->index < (*stack)->a_list->index)
				pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
		}
		print_sorted_list((*stack)->a_list, (*stack)->moves);
	}
	//print_sorted_list((*stack)->a_list, (*stack)->moves);
}

void	push_swap(t_stack *stack)
{
	if (stack->length <= 3)
	{
		sort_three(&stack);
		print_sorted_list(stack->a_list, stack->moves);
	}
	else
	{
		ft_printf("%sDEVELOPING...%s\n", YELLOW, END);
		find_edges(&stack);
		set_indexes(&stack);
		push_to_b(&stack);
		sort_three(&stack);
		print_sorted_list(stack->a_list, stack->moves);
		print_sorted_list(stack->b_list, stack->moves);
		ft_printf("\n");
		sort(&stack);
	}
}

// void	sort(t_stack **stack)
// {
// 	while ((*stack)->b_list != NULL)
// 	{
// 		if (((*stack)->b_list->next)
// 			&& ((*stack)->b_list->index < (*stack)->b_list->next->index))
// 		{
// 			sb(&(*stack)->b_list, &(*stack)->moves);
// 		}
// 		while (((*stack)->a_list->prev->index > (*stack)->b_list->index)
// 			&& ((*stack)->a_list->prev->index != (*stack)->length))
// 		{
// 			rra(&(*stack)->a_list, &(*stack)->moves);
// 		}
// 		pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
// 		if ((*stack)->a_list->index != (*stack)->a_list->next->index - 1)
// 		{
// 			while ((*stack)->a_list->index > (*stack)->a_list->next->index)
// 			{
// 				if ((*stack)->b_list->next
// 					&& (*stack)->b_list->index < (*stack)->b_list->next->index)
// 				{
// 					ss(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
// 				}
// 				else
// 					sa(&(*stack)->a_list, &(*stack)->moves);
// 				if ((*stack)->a_list->next->index - (*stack)->a_list->index > 1)
// 				{
// 					ra(&(*stack)->a_list, &(*stack)->moves);
// 				}
// 			}
// 		}
// 	}
// 	print_sorted_list((*stack)->a_list, (*stack)->moves);
// }
