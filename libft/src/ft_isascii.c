/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:49:54 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/24 11:33:48 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	c;

// 	c = 'a';
// 	if (ft_isascii(c))
// 		printf("It is ascii.\n");
// 	else
// 		printf("It is not ascii.\n");
// }
