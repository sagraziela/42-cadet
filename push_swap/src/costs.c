/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:07:58 by root              #+#    #+#             */
/*   Updated: 2024/03/05 18:16:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	set_cost_a(t_stack ***stack)
{
	int		i;
	t_tab	*temp;

	i = 0;
	while (i < get_list_length((**stack)->a_list))
	{
		(**stack)->a_list->cost_a = 0;
		temp = (**stack)->a_list;
		while (temp->pos != 0)
		{
			if (get_list_length(temp) / 2 < (**stack)->a_list->pos)
			{
				(**stack)->a_list->cost_a--;
				temp = temp->next;
			}
			else
			{
				(**stack)->a_list->cost_a++;
				temp = temp->prev;
			}
		}
        if ((**stack)->a_list->value == 55)
		    ft_printf("A = %d | cost_a = %d\n\n", (**stack)->a_list->value, (**stack)->a_list->cost_a);
		(**stack)->a_list = (**stack)->a_list->next;
		i++;
	}
}

void	set_cost_b(t_stack ***stack)
{
	int		i;
	t_tab	*temp;

	i = 0;
	while (i < get_list_length((**stack)->b_list))
	{
		(**stack)->b_list->cost_b = 0;
		temp = (**stack)->b_list;
		while (temp->pos != 0)
		{
			if (get_list_length(temp) / 2 < (**stack)->b_list->pos)
			{
				(**stack)->b_list->cost_b--;
				temp = temp->next;
			}
			else
			{
				(**stack)->b_list->cost_b++;
				temp = temp->prev;
			}
		}
		//ft_printf("B = %d | pos_b = %d cost_b = %d\n", (**stack)->b_list->value, (**stack)->b_list->pos, (**stack)->b_list->cost_b);
		if ((**stack)->b_list->next)
			(**stack)->b_list = (**stack)->b_list->next;
		i++;
	}
}

void	set_full_cost(t_stack ***stack)
{
	int					i;
	t_tab				*temp_a;
	t_tab				*temp_b;

	i = 0;
	temp_a = (**stack)->a_list;
	temp_b = (**stack)->b_list;
	while (i < get_list_length((**stack)->b_list))
	{
		while ((**stack)->a_list->pos != (**stack)->b_list->target_pos)
		{
            // if ((**stack)->b_list->value == 55)
			//     ft_printf("A = %d | cost = %d\n", (**stack)->a_list->value, (**stack)->a_list->cost_a);
			(**stack)->a_list = (**stack)->a_list->next;
		}
        if ((**stack)->b_list->value == 50)
            ft_printf("A = %d | cost_a = %d | pos: %d\n\n", (**stack)->a_list->value, (**stack)->a_list->cost_a, (**stack)->a_list->pos);
		(**stack)->b_list->cost_a = (**stack)->a_list->cost_a;
		if ((**stack)->a_list->cost_a < 0)
			(**stack)->a_list->cost_a = (**stack)->a_list->cost_a * (-1);
		if ((**stack)->b_list->cost_b < 0)
			(**stack)->a_list->cost_b = (**stack)->b_list->cost_b * (-1);
		else
			(**stack)->a_list->cost_b = (**stack)->b_list->cost_b;
		(**stack)->b_list->cost = (**stack)->a_list->cost_a + (**stack)->a_list->cost_b;
		//ft_printf("value: %d | cost: %d | cost_a: %d | cost_b: %d\n", (**stack)->b_list->value, (**stack)->b_list->cost, (**stack)->a_list->cost_a, (**stack)->b_list->cost_b);
		(**stack)->b_list = (**stack)->b_list->next;
		i++;
	}
	(**stack)->a_list = temp_a;
	(**stack)->b_list = temp_b;
}
