/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:34:51 by gde-souz          #+#    #+#             */
/*   Updated: 2023/09/07 16:57:35 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf_bonus.h"

static int	ft_putnbr_base(long long nbr, char *base)
{
	int		length;
	long	base_len;

	length = 0;
	base_len = (long)ft_strlen(base);
	if (nbr < 0)
	{
		write(1, "-", 1);
		length++;
		nbr *= -1;
	}
	if (nbr >= base_len)
	{
		length += ft_putnbr_base(nbr / base_len, base);
	}
	write(1, &base[nbr % base_len], 1);
	length++;
	return (length);
}

static int	ft_putptr(unsigned long nbr, char *base)
{
	int				length;
	unsigned long	base_len;

	if (!nbr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	length = 0;
	base_len = (long)ft_strlen(base);
	if (nbr < 0)
		nbr *= -1;
	if (nbr >= base_len)
	{
		length += ft_putptr(nbr / base_len, base);
	}
	else
	{
		write(1, "0x", 2);
		length += 2;
	}
	write(1, &base[nbr % base_len], 1);
	length++;
	return (length);
}

static int	check_data_type(char type, va_list args)
{
	int	length;

	length = 0;
	if (type == 'c')
		length += ft_putchar_fd(va_arg(args, int), 1);
	if (type == 's')
		length += ft_putstr_fd(va_arg(args, char *), 1);
	if (type == 'p')
		length += ft_putptr(va_arg(args, unsigned long), HEXALOW);
	if (type == 'd')
		length += ft_putnbr_base(va_arg(args, int), DECIMAL);
	if (type == 'i')
		length += ft_putnbr_base(va_arg(args, int), DECIMAL);
	if (type == 'u')
		length += ft_putnbr_base(va_arg(args, unsigned int), DECIMAL);
	if (type == 'x')
		length += ft_putnbr_base(va_arg(args, unsigned int), HEXALOW);
	if (type == 'X')
		length += ft_putnbr_base(va_arg(args, unsigned int), HEXAUP);
	if (type == '%')
		length += ft_putchar_fd('%', 1);
	return (length);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		length;
	int		i;

	va_start(args, str);
	length = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			length += check_data_type(str[++i], args);
		else
		{
			write(1, &str[i], 1);
			length++;
		}
		i++;
	}
	va_end(args);
	return (length);
}

// int	main(void)
// {
// 	int	res;

// 	res = ft_printf(" NULL %s NULL ", NULL);
// 	printf("%i\n", res);
// 	res = printf(" NULL %s NULL ", NULL);
// 	printf("%i\n", res);
// }
// cc ft_printf.c
// cc *c -g3 -o ft_printf (para debugar)