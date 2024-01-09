/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:21:56 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/09 15:55:19 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	c;

	i = 0;
	c = 'a';
	if (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			if ((argv[1][i] >= 65 && argv[1][i] < 90) ||
				(argv[1][i] >= 97 && argv[1][i] < 122))
			{
				c = argv[1][i] + 1;
				write(1, &c, 1);
			}
			else if (argv[1][i] == 90)
				write(1, "A", 1);
			else if (argv[1][i] == 122)
				write(1, "a", 1);
			else
				write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
