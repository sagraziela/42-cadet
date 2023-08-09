/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:55:26 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/21 12:26:16 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

// #include <unistd.h>

// int	main(void)
// {
// 	char	result[13] = "Hello world!";
// 	int		i;

// 	i = 2;
// 	ft_bzero(result, sizeof(char) * 2);
// 	while (result[i])
// 	{
// 		write(1, &result[i], sizeof(char));
// 		i++;
// 	}
// }
