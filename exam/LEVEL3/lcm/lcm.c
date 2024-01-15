/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:00:13 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/15 11:39:40 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned int	lcm(unsigned int a, unsigned int b)
{
	unsigned int	max;
	unsigned int	res;

	max = a * b;
	res = max;
	if (a == 0 || b == 0)
		return (0);
	while (max >= a && max >= b)
	{
		if (max % a == 0 && max % b == 0)
			res = max;
		max--;
	}
	return (res);
}

int	main(void)
{
	printf("LCM: %u\n", lcm(10, 18));
	return (0);
}
