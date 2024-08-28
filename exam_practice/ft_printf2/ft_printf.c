/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:48:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/28 11:50:13 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

size_t	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

size_t	ft_putnbr_base(long long int nbr, char *base)
{
	size_t	length;
	int		base_len;

	length = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (nbr < 0)
	{
		length += write(1, "-", 1);
		nbr *= -1;
	}
	if (nbr >= base_len)
		length += ft_putnbr_base(nbr / base_len, base);
	length += write(1, &base[nbr % base_len], 1);
	return (length);
}

size_t	decode_var(va_list args, int code)
{
	size_t	length;

	length = 0;
	if (code == 's')
		length += ft_putstr(va_arg(args, char*));
	if (code == 'd')
		length += ft_putnbr_base(va_arg(args, int), DECIMAL);
	if (code == 'x')
		length += ft_putnbr_base(va_arg(args, long unsigned int), HEXA);
	return (length);
}

size_t	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	length;
	int		i;

	va_start(args, str);
	i = 0;
	length = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			length += decode_var(args, str[++i]);
		else
			length += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (length);
}

#include <stdio.h>
#include <limits.h>

int	main(void)
{
	char	*str;
	int		nbr;
	int		size;

	str = "Hello";
	nbr = 42;
	size = ft_printf("%s, it's me.\n", str);
	printf("%d\n", size);
	size = printf("%s, it's me.\n", str);
	printf("%d\n", size);
	size = ft_printf("%s, the magical number is %d.\n", str, nbr);
	printf("%d\n", size);
	size = printf("%s, the magical number is %d.\n", str, nbr);
	printf("%d\n", size);
	size = ft_printf("%s, the hexa of %d id %x.\n", str, nbr, nbr);
	printf("%d\n", size);
	size = printf("%s, the hexa of %d id %x.\n", str, nbr, nbr);
	printf("%d\n", size);
	size = ft_printf("%d | %d | %d.\n", 0, INT_MAX, INT_MIN);
	printf("%d\n", size);
	size = printf("%d | %d | %d.\n", 0, INT_MAX, INT_MIN);
	printf("%d\n", size);
	return (0);
}
