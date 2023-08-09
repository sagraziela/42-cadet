/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:07:42 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/25 13:51:53 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	c;

// 	c = '\n';
// 	if (ft_isprint(c))
// 		printf("It is printable.\n");
// 	else
// 		printf("It is not printable.\n");
// }
