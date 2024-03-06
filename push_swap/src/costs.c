/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:07:58 by root              #+#    #+#             */
/*   Updated: 2024/03/06 11:21:17 by gde-souz         ###   ########.fr       */
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
		if ((**stack)->b_list->next)
			(**stack)->b_list = (**stack)->b_list->next;
		i++;
	}
}

int	sum_costs(int cost_a, int cost_b)
{
	int	cost;

	if (cost_a < 0)
		cost_a *= (-1);
	if (cost_b < 0)
		cost_b *= (-1);
	cost = cost_a + cost_b;
	return (cost);
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
			(**stack)->a_list = (**stack)->a_list->next;
		(**stack)->b_list->cost_a = (**stack)->a_list->cost_a;
		(**stack)->b_list->cost
			= sum_costs((**stack)->a_list->cost_a, (**stack)->b_list->cost_b);
		(**stack)->b_list = (**stack)->b_list->next;
		i++;
	}
	(**stack)->a_list = temp_a;
	(**stack)->b_list = temp_b;
}
