/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/05 19:54:20 by root             ###   ########.fr       */
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

// void	push_to_b(t_stack **stack)
// {
// 	int	i;
// 	int	a_len;

// 	a_len = (*stack)->length;
// 	(*stack)->mid = a_len / 2;
// 	while (a_len > 3)
// 	{
// 		i = 0;
// 		(*stack)->small = (*stack)->mid / 2;
// 		while (i++ < a_len && get_list_length((*stack)->a_list) > 3)
// 		{
// 			//print_sorted_list((*stack)->b_list, (*stack)->moves);
// 			if ((*stack)->a_list->index >= (*stack)->length - 2)
// 				ra(&(*stack)->a_list, &(*stack)->moves);
// 			else
// 			{
// 				pb(&(*stack)->a_list, &(*stack)->b_list, &(*stack)->moves);
// 				if ((*stack)->b_list->next
// 					&& (*stack)->b_list->index < (*stack)->mid)
// 					rb(&(*stack)->b_list, &(*stack)->moves);
// 			}
// 		}
// 		print_sorted_list((*stack)->b_list, (*stack)->moves);
// 		a_len = get_list_length((*stack)->a_list);
// 		(*stack)->mid = (*stack)->length - (a_len / 2);
// 	}
// }

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
		}
		print_sorted_list((*stack)->b_list, (*stack)->moves);
		a_len = get_list_length((*stack)->a_list);
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
			rra(&(*stack)->a_list, &(*stack)->moves);
	}
	print_sorted_list((*stack)->a_list, (*stack)->moves);
}

t_tab	*get_cheapest_nbr(t_tab *list)
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
		//ft_printf("list: %d | cost: %d | cost_a: %d | cost_b: %d\n", list->value, list->cost, list->cost_a, list->cost_b);
		list = list->next;
	}
	return (cheapest);
}

void	sort(t_stack **stack)
{
	int		i;
	t_tab	*cheapest;

	i = 0;
	while ((*stack)->b_list)
	{
		set_positions(&(*stack)->a_list);
		set_positions(&(*stack)->b_list);
		set_target(&stack);
		set_cost_a(&stack);
		set_cost_b(&stack);
		set_full_cost(&stack);
		cheapest = get_cheapest_nbr((*stack)->b_list);
		ft_printf("cheapest: %d | cost: %d | cost_a: %d | cost_b: %d\n", cheapest->value, cheapest->cost, cheapest->cost_a, cheapest->cost_b);
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
		print_sorted_list((*stack)->a_list, (*stack)->moves);
		print_sorted_list((*stack)->b_list, (*stack)->moves);
		i++;
	}
}

void	push_swap(t_stack *stack)
{
	if (stack->length <= 3 && stack->length > 1)
	{
		sort_three(&stack);
		print_sorted_list(stack->a_list, stack->moves);
	}
	else if (stack->length > 3)
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
		find_beginning(&stack);
	}
}
