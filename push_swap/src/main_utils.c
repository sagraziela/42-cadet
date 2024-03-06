/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:13:58 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/06 17:53:37 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	is_sorted(int *nbr)
{
	int	i;

	i = 0;
	while (nbr[i + 1] != '\0' || nbr[i + 1] == 0)
	{
		if (nbr[i] > nbr[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	is_repeated(int *list, int n, int len)
{
	while (list[len] != '\0')
	{
		if (list[len] == n)
			return (1);
		len++;
	}
	return (0);
}

int	get_length(char **nbr_list)
{
	int	i;
	int	j;

	i = 0;
	while (nbr_list[i])
	{
		j = 0;
		while (nbr_list[i][j])
		{
			if ((nbr_list[i][j] < 48 && nbr_list[i][j] != 43
				&& nbr_list[i][j] != 45) || nbr_list[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

void	clear_stack(t_stack **stack)
{
	t_tab	*temp;
	t_tab	*prev;

	while ((*stack)->a_list != NULL)
	{
		if (!(*stack)->a_list->next)
			temp = NULL;
		else if ((*stack)->a_list->next == (*stack)->a_list->prev)
		{
			temp = (*stack)->a_list->next;
			temp->next = NULL;
			temp->prev = NULL;
		}
		else
		{
			prev = (*stack)->a_list->prev;
			temp = (*stack)->a_list->next;
			temp->prev = prev;
			prev->next = temp;
		}
		free((*stack)->a_list);
		(*stack)->a_list = temp;
	}
	free(*stack);
	return ;
}

void	find_beginning(t_stack **stack)
{
	if ((*stack)->length / 2 <= (*stack)->a_list->index)
	{
		while ((*stack)->a_list->index != 1)
			ra(&(*stack)->a_list, &(*stack)->moves);
	}
	else if ((*stack)->length / 2 > (*stack)->a_list->index)
	{
		while ((*stack)->a_list->index != 1)
			rra(&(*stack)->a_list, &(*stack)->moves);
	}
}
