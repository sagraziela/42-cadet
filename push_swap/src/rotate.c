/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:11:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/06 09:38:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ra(t_tab **list)
{
	*list = (*list)->next;
	ft_printf("%sra\n%s", CYAN, END);
	return ;
}

void	rb(t_tab **list)
{
	*list = (*list)->next;
	ft_printf("%srb\n%s", CYAN, END);
	return ;
}

void	rr(t_tab **a_list, t_tab **b_list)
{
	*a_list = (*a_list)->next;
	*b_list = (*b_list)->next;
	ft_printf("%srr\n%s", CYAN, END);
	return ;
}
