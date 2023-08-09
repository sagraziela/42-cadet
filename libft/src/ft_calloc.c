/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:34:44 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/28 17:30:40 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	char	*memory;

	total = nmemb * size;
	if (nmemb == '\0' || size == '\0' || total / size != nmemb)
		return (malloc(0));
	memory = malloc(total);
	if (memory != NULL)
		ft_bzero(memory, total);
	return (memory);
}
