/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:42 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/01 19:08:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_tab	*rra(t_tab *list)
{
	list = list->prev;
	ft_printf("%srra\n%s", CYAN, END);
	return (list);
}

// void	rrb(t_tab **list)
// {}

// void	rrr(t_tab **a_list, t_tab **b_list)
// {}
