/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:54:36 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/28 11:54:35 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	while (n--)
		((char *) dest)[n] = ((char *) src)[n];
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	str[] = "Nuts Channel is Back.";

// 	ft_memmove(str + 2, str, sizeof(char) * 5);
// 	printf("%s", str);
// }
