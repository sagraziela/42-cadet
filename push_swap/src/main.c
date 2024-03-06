/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/06 11:49:47 by gde-souz         ###   ########.fr       */
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
			if ((nbr_list[i][j] < 48 && nbr_list[i][j] != 43
				&& nbr_list[i][j] != 45) || nbr_list[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (i);
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
			clear_char_arr(list);
			return (NULL);
		}
		nbr_list[len] = n;
	}
	clear_char_arr(list);
	return (nbr_list);
}

int	is_sorted(int *nbr)
{
	int	i;

	i = 0;
	while (nbr[i + 1] != '\0')
	{
		if (nbr[i] > nbr[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	*check_validity(char *list, t_stack **stacks)
{
	char	**nbr_list;
	int		*nbr;
	int		len;

	nbr_list = ft_split(list, ' ');
	len = get_length(nbr_list);
	if (len == 0)
	{
		clear_char_arr(nbr_list);
		return (NULL);
	}
	(*stacks)->length = len;
	nbr = char_to_int(nbr_list, len);
	return (nbr);
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

//HOW TO PROCEED IF ARGV[1] IS NOT QUOTED?
	if (argc == 2)
	{
		stacks = init_stacks();
		nbr_arr = check_validity(argv[1], &stacks);
		if (nbr_arr)
		{
			if (!is_sorted(nbr_arr))
			{
				stacks->a_list = create_list(nbr_arr);
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
