/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:04:25 by root              #+#    #+#             */
/*   Updated: 2024/01/18 17:03:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] < 48 || str[i] > 57)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
	return ;
}

void	ft_putnbr(int nbr)
{
	if (nbr < 10)
	{
		nbr += 48;
		write(1, &nbr, 1);
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + 48);
	}
	return ;
}

int	main(int argc, char **argv)
{
	int	i;
	int	nbr;
	int	mult;

	if (argc == 2)
	{
		i = 1;
		nbr = ft_atoi(argv[1]);
		if ((nbr <= 2147483647) || ((nbr * 9) <= 2147483647))
		{
			while (i < 10)
			{
				mult = i * nbr;
				ft_putnbr(i);
				write(1, " x ", 3);
				ft_putnbr(nbr);
				write(1, " = ", 3);
				ft_putnbr(mult);
				write(1, "\n", 1);
				i++;
			}
		}
	}
	else
		write(1, "\n", 1);
	return (0);
}
