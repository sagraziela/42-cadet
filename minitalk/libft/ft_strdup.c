/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:32:12 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/21 13:34:15 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*memory;

	i = 0;
	while (s[i] != '\0')
		i++;
	len = i + 1;
	i = 0;
	memory = malloc(sizeof(char) * len);
	if (memory != NULL)
	{
		while (s[i] != '\0')
		{
			memory[i] = s[i];
			i++;
		}
		memory[i] = '\0';
	}
	return (memory);
}
