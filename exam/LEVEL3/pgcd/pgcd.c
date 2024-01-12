/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:52:42 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/12 16:25:16 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	i;
	int	n1;
	int	n2;
	int	nbr;
	int	result;

	if (argc == 3)
	{
		n1 = atoi(argv[1]);
		n2 = atoi(argv[2]);
		i = 1;
		if (n1 > n2)
			nbr = n2;
		else
			nbr = n1;
		while (i <= nbr)
		{
			if ((n1 % i == 0) && (n2 % i == 0))
				result = i;
			i++;
		}
		printf("%d", result);
	}
	printf("\n");
	return (0);
}
