/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:31:38 by root              #+#    #+#             */
/*   Updated: 2024/01/11 12:47:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	ascii[255] = { 0 };

	if (argc == 3)
	{
		i = 0;
		while (argv[1][i] != '\0')
		{
			j = 0;
			while (argv[2][j] != '\0')
			{
				if (argv[1][i] == argv[2][j] && ascii[argv[1][i]] == 0)
				{
					write(1, &argv[1][i], 1);
					ascii[argv[1][i]] = 1;
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
