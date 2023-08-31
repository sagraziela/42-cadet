/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:44:16 by root              #+#    #+#             */
/*   Updated: 2023/08/31 16:09:46 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 17
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>

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
void	dealloc(t_list **head, char *buffer);

#endif
