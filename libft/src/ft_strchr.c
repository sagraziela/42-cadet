/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:32:41 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/26 16:53:53 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if ((unsigned char) c == '\0')
	{
		return ((char *)s + ft_strlen(s));
	}
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s", ft_strchr("Hello", 108));
// }
