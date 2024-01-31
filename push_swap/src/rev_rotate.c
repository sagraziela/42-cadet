/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:42 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/31 17:36:21 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rra(t_tab **list)
{
	*list = (*list)->prev;
	ft_printf("%srra\n%s", BLUE, END);
	return ;
}

// void	rrb(t_tab **list)
// {}

// void	rrr(t_tab **a_list, t_tab **b_list)
// {}
