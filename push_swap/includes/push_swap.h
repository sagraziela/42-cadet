/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:45:27 by gde-souz          #+#    #+#             */
/*   Updated: 2024/02/19 18:12:56 by root             ###   ########.fr       */
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
void	sort_three(t_stack **stack);
void	push_swap(t_stack *stack);

void	pa(t_tab **a_list, t_tab **b_list);
void	pb(t_tab **a_list, t_tab **b_list);
void	sa(t_tab **list);
void	sb(t_tab **list);
void	ss(t_tab **a_list, t_tab **b_list);
void	ra(t_tab **list);
void	rb(t_tab **list);
void	rr(t_tab **a_list, t_tab **b_list);
void	rra(t_tab **list);
void	rrb(t_tab **list);
void	rrr(t_tab **a_list, t_tab **b_list);

#endif