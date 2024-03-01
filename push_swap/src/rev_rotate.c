/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:42 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/01 11:25:36 by gde-souz         ###   ########.fr       */
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
