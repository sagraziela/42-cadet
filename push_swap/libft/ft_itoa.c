/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:46 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/21 13:32:38 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_digits(long int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		counter++;
	if (n < 0)
	{
		n *= -1;
		counter++;
	}
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

static char	convert_to_char(char *str, long nbr, int len)
{
	int	i;

	i = len - 1;
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (i >= 0 && str[i] != '-')
	{
		str[i] = (nbr % 10) + 48;
		nbr = nbr / 10;
		i--;
	}
	return (*str);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		length;
	char	*str;

	nbr = n;
	length = count_digits(nbr);
	str = ft_calloc((length + 1), sizeof(char));
	if (!str)
		return (NULL);
	convert_to_char(str, nbr, length);
	return (str);
}
