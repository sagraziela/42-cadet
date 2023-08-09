/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:36:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/25 13:51:15 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	if (ft_isalnum('!'))
// 		printf("It is alpha or number.\n");
// 	else
// 		printf("It is neither alpha nor number.\n");
// }
