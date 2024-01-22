/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/22 16:31:49 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	init_stacks(t_stack *stacks)
{
	stacks->a_list = malloc(sizeof(t_list));
	stacks->b_list = malloc(sizeof(t_list));
	stacks->highest = 0;
	stacks->lowest = 0;
	stacks->max_a = 0;
	stacks->max_b = 0;
}

int	fill_stacks(char *list, t_stack *stacks)
{
	int		i;
	int		len;
	char	**nbr_list;
	int		*nbr;

	i = 0;
	len = 0;
	nbr_list = ft_split(list, ' ');
	while (nbr_list[len] != '\0')
		len++;
	nbr = malloc(sizeof(int) * (len + 1));
	if (!nbr)
		return (0);
	while (nbr_list[i] != '\0')
	{
		nbr[i] = ft_atoi(nbr_list[i]);
		if (stacks->highest == 0)
			stacks->highest = nbr[i];
		else
			stacks->highest = nbr[i];
		if (stacks->lowest == 0)
			stacks->lowest = nbr[i];
		else
			stacks->lowest = nbr[i];
		i++;
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
		stacks = malloc(sizeof(t_stack));
		if (!stacks)
			return (0);
		init_stacks(&stacks);
		length = fill_stacks(argv[1], &stacks);
		if (length == 2)
		{}
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
