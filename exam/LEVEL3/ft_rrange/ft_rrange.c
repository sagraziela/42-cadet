/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:43:03 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/15 16:30:38 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

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
	str = malloc((length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	convert_to_char(str, nbr, length);
	return (str);
}

static int	get_size(int start, int end)
{
	int	i;
	int	size;

	i = start;
	size = 0;
	if (start < end)
	{
		while (i <= end)
		{
			size++;
			i++;
		}
	}
	else if (end < start)
	{
		i = end;
		while (i <= start)
		{
			size++;
			i++;
		}
	}
	return (size);
}

int	*ft_rrange(int start, int end)
{
	int	size;
	int	*arr;
	int	i;

	i = 0;
	size = get_size(start, end);
	arr = malloc(sizeof(int) * (size + 1));
	if (!arr)
		return (NULL);
	arr[size] = '\0';
	while (i < size)
	{
		arr[i] = end;
		printf("arr[%d] = %d\n", i, arr[i]);
		i++;
		if (start <= end)
			end--;
		else
			end++;
	}
	printf("\n\n");
	return (arr);
}

int	main(void)
{
	int		*array;
	int		i;

	array = ft_rrange(-3, 2);
	i = 0;
	while (ft_itoa(array[i]))
	{
		printf("%d | ", array[i]);
		i++;
	}
	printf("\n");
	return (0);
}
