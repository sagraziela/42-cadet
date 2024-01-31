/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:11:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/31 17:36:12 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ra(t_tab **list)
{
	*list = (*list)->next;
	ft_printf("%sra\n%s", BLUE, END);
	return ;
}

// void	rb(t_tab **list)
// {}

// void	rr(t_tab **a_list, t_tab *b_list)
// {}
