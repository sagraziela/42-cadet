/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:34:51 by gde-souz          #+#    #+#             */
/*   Updated: 2023/09/06 14:54:37 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr_base(long int nbr, char *base)
{
	int		length;
	int		base_len;

	length = 0;
	base_len = (int)ft_strlen(base);
	if (nbr < 0)
	{
		write(1, "-", 1);
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
// 482
// base = "0123456789abcdef";
// num % 16 = 13;
// base[13] = d

int	check_data_type(char type, va_list args)
{
	int	length;

	length = 0;
	if (type == 'c')
		length += ft_putchar_fd(va_arg(args, int), 1);
	if (type == 's')
		length += ft_putstr_fd(va_arg(args, char *), 1);
	if (type == 'p')
		length += ft_putnbr_base(va_arg(args, unsigned long), HEXALOW);
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

int	main(void)
{
	ft_printf("ft_printf: %x\n", 423467);
	printf("printf: %x\n", 423467);
	//ft_printf("%s | oi!\n", "Hello World!");
	//printf("length printf: %i\n", printf("Hello World! | oi!\n"));
}
// cc ft_printf.c
// cc *c -g3 -o ft_printf (para debugar)