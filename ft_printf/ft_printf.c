/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:34:51 by gde-souz          #+#    #+#             */
/*   Updated: 2023/09/04 13:48:07 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	check_data_type(char type, va_list args)
{
	if (type == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
	}
	return (0);
}

size_t	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	length;
	size_t	i;

	va_start(args, str);
	length = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			check_data_type(str[i + 1], args);
		}
		write(1, &str[i], 1);
		length++;
		i++;
	}
	va_end(args);
	return (length);
}

int	main(void)
{
	ft_printf("%s", "Hello World!");
}
// cc ft_printf.c