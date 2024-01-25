/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:53:26 by root              #+#    #+#             */
/*   Updated: 2024/01/18 14:42:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	is_valid(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 70)
		|| (c >= 97 && c <= 102))
		return (1);
	return (0);
}

char	to_lower(char c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int		i;
	int		sign;
	int		result;
	char	base[16] = "0123456789abcdef";

	i = -1;
	sign = 1;
	result = 0;
	while (!is_valid(str[++i]))
	{
		if (str[i] == '-')
			sign = -1;
	}
	while (is_valid(str[i]))
	{
		result *= str_base;
		if (str[i] >= 48 && str[i] <= 57)
			result += (base[str[i] - 48] - 48);
		else if (str[i] >= 65 && str[i] <= 70)
			result += (base[str[i] - 65] - 38);
		else if (str[i] >= 97 && str[i] <= 102)
			result += (base[str[i] - 97] - 38);
		i++;
	}
	return (result * sign);
}

int	main(void)
{
	printf("%d\n", ft_atoi_base("101010", 2));
	return (0);
}
