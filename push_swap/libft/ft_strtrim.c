/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:55:31 by root              #+#    #+#             */
/*   Updated: 2023/11/21 13:35:13 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*trimmed;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (*s1 == '\0')
		return (ft_calloc(1, sizeof(char)));
	len = ft_strlen(s1);
	while (ft_strrchr(set, s1[len]))
		len--;
	trimmed = ft_calloc((len + 2), sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1, len + 2);
	return (trimmed);
}
