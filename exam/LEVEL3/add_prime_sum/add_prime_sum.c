/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:17:17 by root              #+#    #+#             */
/*   Updated: 2024/01/11 18:37:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] < 48 || str[i] > 57)
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

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

void	ft_putnbr(int nbr)
{
	char	digit;

	if (nbr > 9)
		ft_putnbr(nbr / 10);
	digit = nbr % 10 + 48;
	write(1, &digit, 1);
}

int	main(int argc, char **argv)
{
	int	n;
	int	nbr;
	int	result;

	n = 1;
	result = 0;
	if (argc == 2 && argv[1] >= 0)
	{
		nbr = ft_atoi(argv[1]);
		while (n <= nbr)
		{
			if (check_prime(n))
				result += n;
			n++;
		}
	}
	ft_putnbr(result);
	write(1, "\n", 1);
}
