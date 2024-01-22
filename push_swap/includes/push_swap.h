/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:45:27 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/22 16:01:01 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft.h"

typedef struct s_list {
	int		nbr;
	t_list	*prev;
	t_list	*next;
}	t_list;

typedef struct s_stack {
	t_list	*a_list;
	t_list	*b_list;
	long	highest;
	long	lowest;
	long	max_a;
	long	max_b;
}	t_stack;

int	main(int argc, char **argv);

#endif