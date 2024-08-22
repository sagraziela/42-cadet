/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:09:35 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/22 12:54:22 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# define BUFFER_SIZE 10

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
    unsigned char	c;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);

#endif