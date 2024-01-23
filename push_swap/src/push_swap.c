/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/23 15:41:13 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	init_stacks(t_stack **stacks)
{
	(*stacks)->a_list = NULL;
	(*stacks)->b_list = NULL;
	(*stacks)->highest = 0;
	(*stacks)->lowest = 0;
	(*stacks)->max_a = 0;
	(*stacks)->max_b = 0;
}

int	fill_stacks(char *list, t_stack **stacks)
{
	int		i;
	long	n;
	int		len;
	char	**nbr_list;
	t_tab	*temp;

	i = 0;
	len = 0;
	temp = NULL;
	nbr_list = ft_split(list, ' ');
	while (nbr_list[len])
		len++;
	while (nbr_list[i])
	{
		n = ft_atoi(nbr_list[i]);
		if (n <= INT_MAX && n >= INT_MIN)
		{
			temp = (*stacks)->a_list;
			(*stacks)->a_list = (t_tab *)malloc(sizeof(t_tab) * (len + 1));
			if (!((*stacks)->a_list))
				return (0);
			(*stacks)->a_list->nbr = n;
			temp->next = (*stacks)->a_list;
			if ((*stacks)->highest == 0)
				(*stacks)->highest = n;
			else
				(*stacks)->highest = n;
			if ((*stacks)->lowest == 0)
				(*stacks)->lowest = n;
			else
				(*stacks)->lowest = n;
			ft_printf("nbr[i] = %d\n", (*stacks)->a_list);
			i++;
		}
		else
			return (0);
	}
	nbr[i] = '\0';
	return (len);
}

int	main(int argc, char **argv)
{
	int		i;
	int		length;
	t_stack	*stacks;

	i = 0;
	if (argc == 2)
	{
		ft_printf("Message: %s\n", argv[1]);
		stacks = (t_stack *)malloc(sizeof(t_stack));
		if (!stacks)
			return (0);
		init_stacks(&stacks);
		length = fill_stacks(argv[1], &stacks);
		if (length == 0)
	}
	return (0);
}

//
//
//
//
// rotate
// reverse_rotate
// swap
//
//
//
//
//
