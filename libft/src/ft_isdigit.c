/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:31:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/07/25 13:51:45 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	if (ft_isdigit('9'))
// 		printf("It is digit.\n");
// 	else
// 		printf("It is not digit.\n");
// }
