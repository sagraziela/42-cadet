/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:28:06 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/21 11:54:41 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	if (!s)
	{
		return (NULL);
	}
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

// #include <stdio.h>

// int	main(void)
// {
// 	unsigned char	result[13] = "Hello world!";

// 	ft_memset(result, '*', sizeof(char) * 5);
// 	printf("%s\n", result);
// 	ft_memset(result, '@', sizeof(char) * 2);
// 	printf("%s\n", result);
// }
