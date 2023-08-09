/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:27:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/24 12:41:29 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *) dest;
	s = (char *) src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	source[] = "Hello world!";
// 	char	destination[13];

// 	ft_memcpy(source, destination, sizeof(char) * 8);
// 	printf("%s\n", destination);
// }
