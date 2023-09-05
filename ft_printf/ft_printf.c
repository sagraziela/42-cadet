/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:34:51 by gde-souz          #+#    #+#             */
/*   Updated: 2023/09/05 17:28:37 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

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

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putptr()
{}

int	ft_putnbr_base(unsigned long long int nbr, int base)
{}

int	check_data_type(char type, va_list args)
{
	int	length;

	length = 0;
	if (type == 'c')
		length += ft_putchar_fd(va_arg(args, int), 1);
	if (type == 's')
		length += ft_putstr_fd(va_arg(args, char *), 1);
	if (type == 'p')
		length += ft_putptr_fd(va_arg(args, char *), 1);
	if (type == 'd')
		length += ft_putnbr_base(va_arg(args, char *));
	if (type == 'i')
		length += ft_putnbr_base(va_arg(args, char *));
	if (type == 'u')
		length += ft_putnbr_base(va_arg(args, char *));
	if (type == 'x')
		length += ft_putnbr_base(va_arg(args, char *));
	if (type == 'X')
		length += ft_putnbr_base(va_arg(args, char *));
	if (type == '%')
		length += ft_putnbr_base(va_arg(args, char *));
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
	printf("length ft_printf: %i\n", length);
	return (length);
}

int	main(void)
{
	ft_printf("%s | oi!\n", "Hello World!");
	printf("length printf: %i\n", printf("Hello World! | oi!\n"));
}
// cc ft_printf.c
// cc *c -g3 -o ft_printf (para debugar)