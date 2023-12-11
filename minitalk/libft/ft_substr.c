/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:24:20 by root              #+#    #+#             */
/*   Updated: 2023/11/21 13:35:16 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*memory;

	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len >= s_len)
		len = (s_len - (size_t)start);
	memory = ft_calloc((len + 1), sizeof(char));
	if (memory == NULL)
		return (NULL);
	while (i < len && s[start + i])
	{
		memory[i] = s[start + i];
		i++;
	}
	return (memory);
}
