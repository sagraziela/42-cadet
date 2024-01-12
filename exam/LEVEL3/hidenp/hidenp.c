/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:35:04 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/12 16:57:16 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	counter;

	if (argc == 3)
	{
		i = 0;
		j = 0;
		counter = 0;
		while (argv[1][i] != '\0')
		{
			while (argv[2][j] != '\0' && argv[1][i] != argv[2][j])
				j++;
			if (argv[1][i] == argv[2][j])
				counter++;
			i++;
		}
		if (counter == i)
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
	return (0);
}
