/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/06 12:46:05 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*init_stacks(void)
{
	t_stack	*stacks;

	stacks = (t_stack *)malloc(sizeof(t_stack));
	if (!stacks)
		return (0);
	stacks->a_list = NULL;
	stacks->b_list = NULL;
	stacks->length = 0;
	stacks->moves = 0;
	stacks->highest = 0;
	stacks->lowest = 0;
	stacks->mid = 0;
	stacks->small = 0;
	return (stacks);
}

int	*char_to_int(char **list, int len)
{
	int		*nbr_list;
	long	n;

	nbr_list = (int *)ft_calloc((len + 1), sizeof(int));
	if (!nbr_list)
		return (NULL);
	nbr_list[len] = '\0';
	while (len-- > 0)
	{
		n = ft_atoi(list[len]);
		if (n > 2147483647 || n < -2147483648
			|| is_repeated(nbr_list, n, len + 1))
		{
			free(nbr_list);
			return (NULL);
		}
		nbr_list[len] = n;
	}
	return (nbr_list);
}

int	*check_validity(char **list, t_stack **stacks)
{
	int		*nbr;
	int		len;

	len = get_length(list);
	if (len == 0)
		return (NULL);
	(*stacks)->length = len;
	nbr = char_to_int(list, len);
	return (nbr);
}

int	main(int argc, char **argv)
{
	int		*nbr_arr;
	t_stack	*stacks;

	if (argc > 1)
	{
		stacks = init_stacks();
		nbr_arr = check_validity(++argv, &stacks);
		if (nbr_arr)
		{
			if (!is_sorted(nbr_arr))
			{
				stacks->a_list = create_list(nbr_arr, stacks->length);
				push_swap(stacks);
			}
			free(nbr_arr);
			clear_stack(&stacks);
		}
		else if (!nbr_arr)
		{
			clear_stack(&stacks);
			ft_printf("%sError%s\n", RED, END);
		}
	}
	return (0);
}
