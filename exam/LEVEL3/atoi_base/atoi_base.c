/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:53:26 by root              #+#    #+#             */
/*   Updated: 2024/01/11 20:23:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

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
		return (c - 48);
	else if (c >= 97 && c <= 102)
		return (c + 10 - 'a');
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int		i;
	int		sign;
	int		digit;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		digit = get_digit(to_lower(str[i]), str_base);
		result = (result * str_base) + digit;
		i++;
	}
	return (result * sign);
}

int	main(void)
{
	printf("%d\n", ft_atoi_base("1E", 10));
	return (0);
}
