/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:53:26 by root              #+#    #+#             */
/*   Updated: 2024/01/17 13:26:52 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	to_lower(char c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

int	get_digit(char c, int base)
{
	int	max_digit;

	if (base <= 10)
		max_digit = base + 48;
	else
		max_digit = base + 97;
	if (c >= 48 && c <= 57)
	{
		if (c > max_digit)
			get_digit(c - base, base);
		return (c - 48);
	}
	else if (c >= 97 && c <= 102)
	{
		if (c > max_digit)
			get_digit(c - base, base);
		return (c - 'a' + 10);
	}
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int		i;
	int		x;
	int		factor;
	int		sign;
	int		digit;
	int		result;
	int		len;

	i = 0;
	x = 0;
	sign = 1;
	result = 0;
	len = ft_strlen((char *)str) - 1;
	factor = 1;
	if (str[0] == '-')
		sign = -1;
	while (str[len])
	{
		digit = get_digit(to_lower(str[len]), str_base);
		if (i > 0)
		{
			while (x < i)
			{
				factor *= 16;
				x++;
			}
			i++;
			x = 0;
		}
		else
			i++;
		result += (digit * factor);
		len--;
	}
	return (result * sign);
}

int	main(void)
{
	printf("%d\n", ft_atoi_base("2a", 2));
	return (0);
}
