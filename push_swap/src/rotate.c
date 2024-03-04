/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:11:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/03/04 11:43:35 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ra(t_tab **list, int *moves)
{
	*list = (*list)->next;
	(*moves)++;
	ft_printf("%sra\n%s", CYAN, END);
	return ;
}

void	rb(t_tab **list, int *moves)
{
	*list = (*list)->next;
	(*moves)++;
	ft_printf("%srb\n%s", CYAN, END);
	return ;
}

void	rr(t_tab **a_list, t_tab **b_list, int *moves)
{
	*a_list = (*a_list)->next;
	*b_list = (*b_list)->next;
	(*moves)++;
	ft_printf("%srr\n%s", CYAN, END);
	return ;
}
