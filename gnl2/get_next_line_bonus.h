/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:44:16 by root              #+#    #+#             */
/*   Updated: 2023/09/01 17:01:18 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	unsigned char	content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*create_node(char c);
t_list	*ft_lstadd(t_list *lst, char *buffer, t_list *head);
int		find_line_break(t_list *list);
size_t	find_line_len(t_list *list);
t_list	*dealloc(t_list *head, char *buffer);

#endif
