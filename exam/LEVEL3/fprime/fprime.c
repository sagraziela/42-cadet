/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:44:51 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/12 12:15:40 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	check_prime(int n)
{
	int	i;
	int	counter;

	i = 1;
	counter = 0;
	while (i <= n)
	{
		if (n % i == 0)
			counter++;
		i++;
	}
	if (counter == 2)
		return (1);
	else
		return (0);
}

int	main(int argc, char **argv)
{
	int	nbr;
	int	i;

	if (argc == 2)
	{
		nbr = atoi(argv[1]);
		i = 1;
		while (i <= nbr)
		{
			if (nbr % i == 0)
			{
				if (check_prime(i))
				{
					printf("%d", i);
					nbr /= i;
					if (nbr != 1)
						printf("*");
					i = 0;
				}
			}
			i++;
		}
	}
	printf("\n");
	return (0);
}
