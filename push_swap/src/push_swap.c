/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/06 14:52:55 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_three(t_stack **stack)
{
	if ((*stack)->a_list->value > (*stack)->a_list->next->value
		&& (*stack)->a_list->value > (*stack)->a_list->prev->value)
		ra(&(*stack)->a_list, &(*stack)->moves);
	if ((*stack)->a_list->prev->value < (*stack)->a_list->next->value)
		rra(&(*stack)->a_list, &(*stack)->moves);
	if ((*stack)->a_list->value > (*stack)->a_list->next->value)
		sa(&(*stack)->a_list, &(*stack)->moves);
}

int	check_five(t_stack **stack)
{
	int	i;

	i = 0;
	if ((*stack)->length == 5)
	{
		while (i++ < (*stack)->length
			&& (*stack)->a_list->value > (*stack)->a_list->next->value)
			(*stack)->a_list = (*stack)->a_list->next;
		(*stack)->a_list = (*stack)->a_list->next;
		if (i == (*stack)->length)
		{
			ft_printf("CHEGOU AQUI\n");
			pb(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
			pb(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
			ra(&(*stack)->a_list, &(*stack)->moves);
			sa(&(*stack)->a_list, &(*stack)->moves);
			pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
			ra(&(*stack)->a_list, &(*stack)->moves);
			pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
			ra(&(*stack)->a_list, &(*stack)->moves);
			return (1);
		}
	}
	return (0);
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
		while (i++ < a_len && get_list_length((*stack)->a_list) > 3)
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
		}
		a_len = get_list_length((*stack)->a_list);
		(*stack)->mid = (*stack)->length - (a_len / 2);
	}
}

void	sort(t_stack **stack, t_tab *cheapest)
{
	while (cheapest->cost_a != 0 || cheapest->cost_b != 0)
	{
		if (cheapest->cost_a < 0)
		{
			rra(&(*stack)->a_list, &(*stack)->moves);
			cheapest->cost_a++;
		}
		else if (cheapest->cost_a > 0)
		{
			ra(&(*stack)->a_list, &(*stack)->moves);
			cheapest->cost_a--;
		}
		if (cheapest->cost_b < 0)
		{
			rrb(&(*stack)->b_list, &(*stack)->moves);
			cheapest->cost_b++;
		}
		else if (cheapest->cost_b > 0)
		{
			rb(&(*stack)->b_list, &(*stack)->moves);
			cheapest->cost_b--;
		}
	}
	pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
}

void	push_swap(t_stack *stack)
{
	t_tab	*cheapest;

	if (stack->length <= 3 && stack->length > 1)
		sort_three(&stack);
	else if (stack->length > 3 && !check_five(&stack))
	{
		find_edges(&stack);
		set_indexes(&stack);
		push_to_b(&stack);
		sort_three(&stack);
		while (stack->b_list)
		{
			set_positions(&stack->a_list);
			set_positions(&stack->b_list);
			set_target(&stack);
			set_cost_a(&stack);
			set_cost_b(&stack);
			set_full_cost(&stack);
			cheapest = get_cheapest_nbr(stack->b_list);
			sort(&stack, cheapest);
		}
		find_beginning(&stack);
	}
	//print_sorted_list(stack->a_list, stack->moves);
}
