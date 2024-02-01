/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:11:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/01 19:09:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_tab	*ra(t_tab *list)
{
	list = list->next;
	ft_printf("%sra\n%s", CYAN, END);
	return (list);
}

// void	rb(t_tab **list)
// {}

// void	rr(t_tab **a_list, t_tab *b_list)
// {}
