/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:44:16 by root              #+#    #+#             */
/*   Updated: 2023/08/28 15:19:04 by gde-souz         ###   ########.fr       */
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
void	*ft_malloc(size_t size);
t_list	*ft_lstadd(t_list *lst, char content);
t_list	*create_nodes(t_list *list, char *buffer, int rd);
int		find_line_break_buffer(char *buffer);
size_t	find_line_break_list(t_list *list);

#endif
