/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:42 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/22 19:02:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rra(t_tab **list, int *moves)
{
	*list = (*list)->prev;
	(*moves)++;
	ft_printf("%srra\n%s", CYAN, END);
	return ;
}

void	rrb(t_tab **list, int *moves)
{
	*list = (*list)->prev;
	(*moves)++;
	ft_printf("%srrb\n%s", CYAN, END);
	return ;
}

void	rrr(t_tab **a_list, t_tab **b_list, int *moves)
{
	*a_list = (*a_list)->prev;
	*b_list = (*b_list)->prev;
	(*moves)++;
	ft_printf("%srrr\n%s", CYAN, END);
	return ;
}
