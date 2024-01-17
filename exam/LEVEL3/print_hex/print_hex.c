/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:43:47 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/17 12:10:02 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_atoi(char *nbr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nbr[i] && (nbr[i] < 48 || nbr[i] > 57))
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i] >= 48 && nbr[i] <= 57)
	{
		res = (res * 10) + (nbr[i] - 48);
		i++;
	}
	return (res * sign);
}

void	dec_to_hex(int num)
{
	char	hex[16] = "0123456789abcdef";

	if (num >= 16)
	{
		dec_to_hex(num / 16);
	}
	write(1, &hex[num % 16], 1);
}

int	main(int argc, char **argv)
{
	int		i;
	int		num;

	i = 0;
	if (argc == 2)
	{
		num = ft_atoi(argv[1]);
		dec_to_hex(num);
	}
	write(1, "\n", 1);
	return (0);
}
