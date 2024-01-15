/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:31:34 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/15 16:39:16 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_list.h"

int	ft_list_size(t_list *begin_list)
{
	int		size;

	size = 0;
	if (begin_list)
	{
		while (begin_list->next != NULL)
		{
			size++;
			begin_list = begin_list->next;
		}
		size++;
	}
	return (size);
}
