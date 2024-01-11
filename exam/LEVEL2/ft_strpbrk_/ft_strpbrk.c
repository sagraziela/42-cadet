/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:34:13 by root              #+#    #+#             */
/*   Updated: 2024/01/11 11:09:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	i;
	int	j;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	while (s2[j] != '\0')
	{
		i = 0;
		while (s1[i] != '\0')
		{
			if (s1[i] == s2[j])
				return ((char *)s1 + i);
			i++;
		}
		j++;
	}
	return (NULL);
}

int	main(void)
{
	printf("%s\n", ft_strpbrk("lapiseira", "zsq"));
	return (0);
}
