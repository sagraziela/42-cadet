/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:45:27 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/23 15:16:32 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "./libft.h"

typedef struct s_tab {
	int				nbr;
	struct t_tab	*prev;
	struct t_tab	*next;
}	t_tab;

typedef struct s_stack {
	t_tab	*a_list;
	t_tab	*b_list;
	long	highest;
	long	lowest;
	long	max_a;
	long	max_b;
}	t_stack;

int	main(int argc, char **argv);

#endif