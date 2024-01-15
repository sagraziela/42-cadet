/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:43:47 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/15 16:58:55 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int		i;
	int		num;
	char	hex[16] = "0123456789abcdef";

	i = 0;
	if (argc == 2)
	{
		num = ft_atoi(argv[1]);
		if (num >= 0 && num <= 16)
			write(1, &hex[num], 1);
		else
		{
			while (num)
			{

			}
		}
	}
	write(1, "\n", 1);
	return (0);
}
