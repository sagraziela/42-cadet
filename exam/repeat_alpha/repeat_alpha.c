/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:06:58 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/16 14:26:41 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	repeat;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	repeat = 0;
	while (argv[1][i] != '\0')
	{
		j = 0;
		if (argv[1][i] >= 97 && argv[1][i] <= 122)
		{
			repeat = argv[1][i] - 96;
			while (j++ < repeat)
				write(1, &argv[1][i], 1);
		}
		else if (argv[1][i] >= 65 && argv[1][i] <= 90)
		{
			repeat = argv[1][i] - 64;
			while (j++ < repeat)
				write(1, &argv[1][i], 1);
		}
		else
			write(1, &argv[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
