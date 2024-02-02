/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:45:27 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/02 12:23:21 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define RED     		"\033[1;31m"
# define GREEN   		"\033[1;32m"
# define YELLOW 		"\033[1;33m"
# define BLUE   	 	"\033[1;34m"
# define MAGENTA    	"\033[1;35m"
# define CYAN    		"\033[1;36m"
# define WHITE    		"\033[1;37m"
# define END   			"\033[0m"
# include <limits.h>
# include "./libft.h"

typedef struct s_tab
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_tab	*prev;
	struct s_tab	*next;
}	t_tab;

typedef struct s_stack {
	t_tab	*a_list;
	t_tab	*b_list;
	int		length;
	long	highest;
	long	lowest;
	long	max_a;
	long	max_b;
}	t_stack;

int		main(int argc, char **argv);
t_tab	*create_new_node(int content);
void	ft_lstadd_node(t_tab **lst, t_tab *new);
t_tab	*create_list(int *list);
void	sort_three(t_tab **list);
void	push_swap(t_stack *stack);

void	pa(t_tab **a_list, t_tab **b_list);
void	pb(t_tab **a_list, t_tab **b_list);
t_tab	*sa(t_tab *list);
t_tab	*sb(t_tab *list);
void	ss(t_tab **a_list, t_tab **b_list);
t_tab	*ra(t_tab *list);
t_tab	*rb(t_tab *list);
t_tab	*rr(t_tab *a_list, t_tab *b_list);
t_tab	*rra(t_tab *list);
t_tab	*rrb(t_tab *list);
t_tab	*rrr(t_tab *a_list, t_tab *b_list);

#endif