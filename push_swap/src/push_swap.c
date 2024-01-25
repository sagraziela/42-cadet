/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/25 18:44:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	init_stacks(t_stack **stacks)
{
	(*stacks)->a_list = NULL;
	(*stacks)->b_list = NULL;
	(*stacks)->length = 0;
	(*stacks)->highest = 0;
	(*stacks)->lowest = 0;
	(*stacks)->max_a = 0;
	(*stacks)->max_b = 0;
}

int	*check_validity(char *list, t_stack **stacks)
{
	char	**nbr_list;
	int		*nbr;
	int		len;
	int		n;
	
	len = 0;
	nbr_list = ft_split(list, ' ');
	while (nbr_list[len])
		len++;
	(*stacks)->length = len;
	nbr = (int *)malloc(sizeof(int) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len--] = '\0';
	while (nbr[len--])
	{
		n = ft_atoi(list[len]);
		if (n > 2147483647 || n < -2147483648)
		{
			//free(nbr);
			//free(list);
			return (NULL);
		}
		nbr[len] = n;
	}
	
}

int	fill_stacks(char *list, t_stack **stacks)
{
	int		i;
	long	n;
	t_tab	*new_node;
	t_tab	*temp;

	i = 0;
	temp = NULL;
	while (nbr_list[i])
	{
		n = ft_atoi(nbr_list[i]);
		if (n <= INT_MAX && n >= INT_MIN)
		{
			if ((*stacks)->a_list != NULL)
				temp = (*stacks)->a_list;
			else
				temp = new_node;
			new_node = (t_tab *)malloc(sizeof(t_tab) * ((*stacks)->length + 1));
			if (!(new_node))
				return (0);
			new_node->value = n;
			new_node->index = 8;
			new_node->next = NULL;
			temp = new_node;
			temp->next = new_node;
			ft_lstadd_back((*stacks)->a_list, new_node);
			ft_printf("nbr[i] = %d\n", new_node);
			i++;
		}
		else
			return (0);
	}
	return (len);
}

int	main(int argc, char **argv)
{
	int		i;
	int		*nbr_list;
	t_stack	*stacks;

	i = 0;
	if (argc == 2)
	{
		ft_printf("Message: %s\n", argv[1]);
		stacks = (t_stack *)malloc(sizeof(t_stack));
		if (!stacks)
			return (0);
		init_stacks(&stacks);
		nbr_list = check_validity(argv[1]);
		if (nbr_list)
			fill_stacks(nbr_list, &stacks);
		else
			ft_printf("%sError\n", BLUE);
	}
	ft_printf("%sHELLO\n", BLUE);
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
