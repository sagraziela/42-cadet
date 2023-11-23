/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:09:54 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/21 13:34:54 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *)&big[i]);
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	while (big[i] && i < len)
	{
		while ((big[i + j] == little[j]) && (i + j < len))
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		else
			j = 0;
		i++;
	}
	return (NULL);
}
