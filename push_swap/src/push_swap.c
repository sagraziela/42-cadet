/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/01 17:04:30 by gde-souz         ###   ########.fr       */
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
			//print_sorted_list((*stack)->b_list, (*stack)->moves);
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

void	find_beginning(t_stack **stack)
{
	if ((*stack)->length / 2 < (*stack)->a_list->index)
	{
		while ((*stack)->a_list->index != 1)
			ra(&(*stack)->a_list, &(*stack)->moves);
	}
	else if ((*stack)->length / 2 > (*stack)->a_list->index)
	{
		while ((*stack)->a_list->index != 1)
		{
			ft_printf("HELLO ---- %d -- idx: %d\n", (*stack)->a_list->value, (*stack)->a_list->index);
			rra(&(*stack)->a_list, &(*stack)->moves);
		}
	}
	print_sorted_list((*stack)->a_list, (*stack)->moves);
}

void	get_cheapest_nbr(t_tab *list)
{
	t_tab	*temp;
	t_tab	*cheapest;

	cheapest = list;
	temp = list;
	list = list->next;
	while (list && list != temp)
	{
		if (list->cost < cheapest->cost)
			cheapest = list;
		list = list->next;
	}
}

void	sort(t_stack **stack)
{
	int		i;

	i = 0;
	while ((*stack)->b_list)
	{
		set_positions(&stack);
		set_target(&stack);
		set_cost_a(&stack);
		set_cost_b(&stack);
		set_full_cost(&stack);
		get_cheapest_nbr((*stack)->b_list);
		ft_printf("b_list: %d | cost: %d | cost_a: %d | cost_b: %d\n", (*stack)->b_list->value, (*stack)->b_list->cost, (*stack)->b_list->cost_a, (*stack)->b_list->cost_b);
		while ((*stack)->b_list->cost_a != 0 || (*stack)->b_list->cost_b != 0)
		{
			if ((*stack)->b_list->cost_a < 0)
			{
				rra(&(*stack)->a_list, &(*stack)->moves);
				(*stack)->b_list->cost_a++;
			}
			else if ((*stack)->b_list->cost_a > 0)
			{
				ra(&(*stack)->a_list, &(*stack)->moves);
				(*stack)->b_list->cost_a--;
			}
			if ((*stack)->b_list->cost_b < 0)
			{
				rrb(&(*stack)->b_list, &(*stack)->moves);
				(*stack)->b_list->cost_b++;
			}
			else if ((*stack)->b_list->cost_b > 0)
			{
				rb(&(*stack)->b_list, &(*stack)->moves);
				(*stack)->b_list->cost_b--;
			}
		}
		pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
		//ft_printf("A: %d\n", (*stack)->a_list->value);
		print_sorted_list((*stack)->a_list, (*stack)->moves);
		i++;
	}
}

// void	sort(t_stack **stack)
// {
// 	while ((*stack)->b_list)
// 	{
// 		set_positions(&stack);
// 		set_target(&stack);
// 		set_cost_a(&stack);
// 		set_cost_b(&stack);
// 		while ((*stack)->b_list
// 			&& (*stack)->b_list->target_pos != (*stack)->a_list->pos)
// 		{
// 			if (get_list_length((*stack)->a_list) / 2
// 				> (*stack)->b_list->target_pos)
// 				ra(&(*stack)->a_list, &(*stack)->moves);
// 			else if (get_list_length((*stack)->a_list) / 2
// 				< (*stack)->b_list->target_pos)
// 				rra(&(*stack)->a_list, &(*stack)->moves);
// 		}
// 		pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
// 		//print_sorted_list((*stack)->a_list, (*stack)->moves);
// 	}
// }

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
		//find_beginning(&stack);
	}
}

// void	sort(t_stack **stack)
// {
// 	while ((*stack)->b_list)
// 	{
// 		set_positions(&stack);
// 		set_target(&stack);
// 		set_cost_a(&stack);
// 		set_cost_b(&stack);
// 		while ((*stack)->b_list
// 			&& (*stack)->b_list->target_pos != (*stack)->a_list->pos)
// 		{
// 			if (get_list_length((*stack)->a_list) / 2
// 				> (*stack)->b_list->target_pos)
// 				ra(&(*stack)->a_list, &(*stack)->moves);
// 			else if (get_list_length((*stack)->a_list) / 2
// 				< (*stack)->b_list->target_pos)
// 				rra(&(*stack)->a_list, &(*stack)->moves);
// 		}
// 		pa(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
// 		//print_sorted_list((*stack)->a_list, (*stack)->moves);
// 	}
// }