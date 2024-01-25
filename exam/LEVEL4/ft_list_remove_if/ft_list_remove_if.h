/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:26:30 by root              #+#    #+#             */
/*   Updated: 2024/01/18 18:42:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_REMOVE_IF_H
# define FT_LIST_REMOVE_IF_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}			t_list;

#endif
