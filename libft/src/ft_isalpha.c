/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:54:56 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/24 11:33:32 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	if (ft_isalpha('g'))
// 		printf("It is alpha.\n");
// 	else
// 		printf("It is not alpha.\n");
// }
