/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/29 17:38:34 by gde-souz         ###   ########.fr       */
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
	ft_printf("len = %d\n", len);
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
			free(nbr_list);
			return (NULL);
		}
		nbr[len] = n;
	}
	free(nbr_list);
	return (nbr);
}

void	ft_lstadd_node(t_tab **lst, t_tab *new)
{
	t_tab	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		while ((*lst)->next != NULL)
			last = (*lst)->next;
		last->next = new;
	}
}

t_tab	*create_list(int *list)
{
	int		i;
	t_tab	*new_node;
	t_tab	*head;
	t_tab	*temp;

	i = 0;
	temp = NULL;
	head = NULL;
	new_node = (t_tab *)malloc(sizeof(t_tab));
	if (!new_node)
		return (NULL);
	while (list[i])
	{
		// FALTA COMPLEMENTAR PARA SALVAR O HEAD!
		new_node->value = list[i];
		new_node->index = 0;
		new_node->next = NULL;
		new_node->prev = temp;
		ft_lstadd_node(&head, new_node);
		ft_printf("node[i] = %d\n", new_node->value);
		temp = new_node;
		temp->next = new_node;
		i++;
	}
	return (head);
}

int	main(int argc, char **argv)
{
	int		i;
	int		*nbr_arr;
	t_stack	*stacks;

	i = 0;
	if (argc == 2)
	{
		ft_printf("Message: %s\n", argv[1]);
		stacks = (t_stack *)malloc(sizeof(t_stack));
		if (!stacks)
			return (0);
		init_stacks(&stacks);
		nbr_arr = check_validity(argv[1], &stacks);
		if (nbr_arr)
			stacks->a_list = create_list(nbr_arr);
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
