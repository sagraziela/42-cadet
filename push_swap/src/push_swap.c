/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/31 15:57:08 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	handle_three(t_tab *list)
{
	if (list->value > list->next->value && list->value < list->prev->value)
		sa(&list);
	else if (list->value < list->next->value && list->value < list->prev->value)
	{
		rra(&list);
		sa(&list);
	}
	else if (list->value < list->next->value && list->value > list->prev->value)
		rra(&list);
	else if (list->value > list->next->value && list->value > list->prev->value)
		ra(&list);
}

//  1 2 3
//  1 3 2
//  2 1 3
//  2 3 1
//  3 1 2
//  3 2 1

void	push_swap(t_stack *stack)
{
	t_tab	*list;

	list = stack->a_list;
	if (stack->length == 2)
	{
		if (list->value > list->next->value)
			sa(stack->a_list);
		else
			ft_printf("%sOK\n%s", GREEN, END);
	}
	else if (stack->length == 3)
	{
		handle_three(stack->a_list);
	}
}
