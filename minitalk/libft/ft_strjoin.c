/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:40:25 by root              #+#    #+#             */
/*   Updated: 2023/11/21 13:34:22 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	fill_mem(char *mem, const char *str1, const char *str2,
	int total_len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < total_len)
	{
		if (str1[j])
		{
			mem[i] = str1[j];
			j++;
			i++;
		}
		else
		{
			mem[i] = str2[i - j];
			i++;
		}
	}
	mem[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	char	*joined;

	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	joined = (char *)malloc(sizeof(char) * (total_len + 1));
	if (joined == NULL)
		return (NULL);
	fill_mem(joined, s1, s2, total_len);
	return (joined);
}
