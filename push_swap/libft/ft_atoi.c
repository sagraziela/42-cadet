/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:22:22 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/23 15:15:42 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	long	sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if ((nptr[i] == '+'))
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	return (res * sign);
}
