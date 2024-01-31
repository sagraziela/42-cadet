/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:36:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/31 17:36:32 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	handle_three(t_tab *list)
{
	t_tab	*lst;
	//int		i;

	lst = list;
	if (lst->value > lst->next->value && lst->value > lst->prev->value)
		ra(&lst);
	if ((lst->value < lst->next->value && lst->value < lst->prev->value)
		|| (lst->value < lst->next->value && lst->value > lst->prev->value))
		rra(&lst);
	if (lst->value > lst->next->value)
		sa(&lst);
	// i = 0;
	// while (i < 3)
	// {
	// 	ft_printf("list = %d\n", list->value);
	// 	list = list->next;
	// 	i++;
	// }
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
			sa(&stack->a_list);
		else
			ft_printf("%sOK\n%s", GREEN, END);
	}
	else if (stack->length == 3)
	{
		handle_three(stack->a_list);
	}
}
