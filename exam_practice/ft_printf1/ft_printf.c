/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:26:10 by root              #+#    #+#             */
/*   Updated: 2024/08/21 16:13:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static size_t	ft_putchar_fd(char c, int fd)
{
	if (!c)
		return (write(fd, "(null)", 7));
	write(fd, &c, 1);
	return (1);
}

static size_t	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr_fd("(null)", 1));
	while (str[i])
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
	return (i);
}

static size_t	ft_putnbr_base(long long nbr, char *base, int is_ptr)
{
	long	base_len;
	size_t	length;

	base_len = 0;
	if (!nbr)
		return(ft_putstr_fd("(nil)", 1));
	if ((nbr > 2147483647 || nbr < -2147483647) && (base_len == 16 || base_len == 8))
		return(ft_putstr_fd("(nil)", 1));
	while (base[base_len])
		base_len++;
	length = 0;
	if (nbr < 0)
	{
		length += ft_putchar_fd('-', 1);
		nbr *= -1;
	}
	if (nbr >= base_len)
		length += ft_putnbr_base(nbr / base_len, base, is_ptr);
	else if (is_ptr && nbr < base_len)
		length += ft_putstr_fd("0x", 1);
	length += ft_putchar_fd(base[nbr % base_len], 1);
	return (length);
}

static size_t	get_var_value(char c, va_list args)
{
	size_t	length;

	length = 0;
	if (c == 'c')
		length += ft_putchar_fd(va_arg(args, int), 1);
	if (c == 's')
		length += ft_putstr_fd(va_arg(args, char *), 1);
	if (c == 'd')
		length += ft_putnbr_base(va_arg(args, int), DECIMAL, 0);
	if (c == 'i')
		length += ft_putnbr_base(va_arg(args, int), DECIMAL, 0);
	if (c == 'u')
		length += ft_putnbr_base(va_arg(args, unsigned long), DECIMAL, 0);
	if (c == 'o')
		length += ft_putnbr_base(va_arg(args, unsigned long), OCTAL, 0);
	if (c == 'p')
		length += ft_putnbr_base(va_arg(args, unsigned long), LOW_HEXA, 1);
	if (c == 'x')
		length += ft_putnbr_base(va_arg(args, unsigned long), LOW_HEXA, 0);
	if (c == 'X')
		length += ft_putnbr_base(va_arg(args, unsigned long), HIGH_HEXA, 0);
	if (c == '%')
		length += ft_putchar_fd('%', 1);
	return (length);
}

size_t	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	length;
	int		i;

	va_start(args, str);
	length = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			length += get_var_value(str[++i], args);
		}
		else
		{
			length += write(1, &str[i], 1);
		}
		i++;
	}
	va_end(args);
	return (length);
}

// cc -Wall -Wextra -Werror -g ./main.c ./ft_printf.c -I./
