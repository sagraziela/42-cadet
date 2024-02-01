/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/01 19:04:06 by root             ###   ########.fr       */
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

void	handle_three(t_tab **list)
{
	if ((*list)->value > (*list)->next->value 
		&& (*list)->value > (*list)->prev->value)
		*list = ra(*list);
	if ((*list)->prev->value < (*list)->next->value)
		*list = rra(*list);
	if ((*list)->value > (*list)->next->value)
		*list = sa(*list);
}

//  1 2 3
//  1 3 2 | rra | 2 1 3
//  2 1 3 | sa  | 1 2 3
//  2 3 1 | rra | 1 2 3
//  3 1 2 | ra  | 1 2 3
//  3 2 1 | ra  | 2 1 3

void	push_swap(t_stack *stack)
{
	t_tab	*list;

	list = stack->a_list;
	if (stack->length == 2)
	{
		if (list->value > list->next->value)
			stack->a_list = sa(stack->a_list);
		else
			ft_printf("%sOK\n%s", GREEN, END);
	}
	else if (stack->length == 3)
	{
		handle_three(&stack->a_list);
		print_sorted_list(stack->a_list, stack->length);
	}
	else
	{
		ft_printf("%sDEVELOPING...%s\n", YELLOW, END);
	}
}
