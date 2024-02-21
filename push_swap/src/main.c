/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/21 15:39:14 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	init_stacks(t_stack **stacks)
{
	(*stacks)->a_list = NULL;
	(*stacks)->b_list = NULL;
	(*stacks)->length = 0;
	(*stacks)->moves = 0;
	(*stacks)->highest = 0;
	(*stacks)->lowest = 0;
	(*stacks)->max_a = 0;
	(*stacks)->max_b = 0;
}

void	clear_char_arr(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
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
			if (nbr_list[i][j] < 48 || nbr_list[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

int	*check_validity(char *list, t_stack **stacks)
{
	char	**nbr_list;
	int		*nbr;
	int		len;
	long	n;

	nbr_list = ft_split(list, ' ');
	len = get_length(nbr_list);
	if (len == 0)
	{
		clear_char_arr(nbr_list);
		return (NULL);
	}
	(*stacks)->length = len;
	nbr = (int *)malloc(sizeof(int) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len] = '\0';
	while (len-- > 0)
	{
		n = ft_atoi(nbr_list[len]);
		if (n > 2147483647 || n < -2147483648)
		{
			free(nbr);
			clear_char_arr(nbr_list);
			return (NULL);
		}
		nbr[len] = n;
	}
	clear_char_arr(nbr_list);
	return (nbr);
	// FALTA VERIFICAR SE TEM NÚMERO REPETIDO!
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

int	main(int argc, char **argv)
{
	int		*nbr_arr;
	t_stack	*stacks;

	if (argc == 2)
	{
		stacks = (t_stack *)malloc(sizeof(t_stack));
		if (!stacks)
			return (0);
		init_stacks(&stacks);
		//REVIEW CHECK_VALIDITY() - IT DOES NOT RECEIVE NEGATIVE INT!
		nbr_arr = check_validity(argv[1], &stacks);
		if (nbr_arr)
		{
			stacks->a_list = create_list(nbr_arr);
			free(nbr_arr);
			push_swap(stacks);
			clear_stack(&stacks);
		}
		else
			ft_printf("%sError%s\n", RED, END);
	}
	return (0);
}
