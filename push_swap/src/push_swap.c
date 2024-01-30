/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/30 13:25:53 by root             ###   ########.fr       */
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

int	*check_validity(char *list, t_stack **stacks)
{
	char	**nbr_list;
	int		*nbr;
	int		len;
	long	n;

	len = 0;
	nbr_list = ft_split(list, ' ');
	while (nbr_list[len])
		len++;
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
}

t_tab	*create_new_node(int content)
{
	t_tab	*new_node;

	new_node = (t_tab *)malloc(sizeof(t_tab));
	if (!new_node)
		return (NULL);
	new_node->value = content;
	new_node->index = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	ft_lstadd_node(t_tab **lst, t_tab *new)
{
	t_tab	*temp;
	t_tab	*last;

	last = NULL;
	if ((*lst) == NULL)
		(*lst) = new;
	else
	{
		if ((*lst)->next == NULL)
			last = *lst;
		else
		{
			temp = *lst;
			while (temp->next != NULL)
			{
				last = temp->next;
				temp = temp->next;
			}
		}
		last->next = new;
		new->prev = last;
	}
}

t_tab	*create_list(int *list)
{
	int		i;
	t_tab	*new_node;
	t_tab	*head;

	i = 0;
	head = NULL;
	while (list[i])
	{
		new_node = create_new_node(list[i]);
		ft_lstadd_node(&head, new_node);
		i++;
	}
	ft_printf("%sHEAD = %d%s\n", GREEN, head->value, END);
	return (head);
}

int	main(int argc, char **argv)
{
	int		*nbr_arr;
	t_stack	*stacks;
	t_tab	*temp;

	if (argc == 2)
	{
		stacks = (t_stack *)malloc(sizeof(t_stack));
		if (!stacks)
			return (0);
		init_stacks(&stacks);
		nbr_arr = check_validity(argv[1], &stacks);
		if (nbr_arr)
		{
			stacks->a_list = create_list(nbr_arr);
			free(nbr_arr);
			temp = stacks->a_list;
			while (temp)
			{
				ft_printf("node = %d\n", temp->value);
				temp = temp->next;
			}
		}
		else
			ft_printf("%sError%s\n", MAGENTA, END);
	}
	ft_printf("sizeof t_stack: %d\n", sizeof(t_stack));
	ft_printf("%sHELLO%s\n", MAGENTA, END);
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
