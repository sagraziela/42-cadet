/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:37:02 by gde-souz          #+#    #+#             */
/*   Updated: 2023/09/15 15:07:42 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	apply_plus_space(char **flag)
{
	if (*flag[0] == '+')
	{
		write(1, "+", 1);
	}
	else if (*flag[0] == ' ')
	{
		if (*flag[1] == '+')
			write(1, "+", 1);
		else
			write (1, " ", 1);
	}
	return (1);
}

static int	apply_hash(char data, va_list args)
{
	int				length;
	unsigned int	arg;

	length = 0;
	arg = va_arg(args, unsigned int);
	if (arg == 0)
	{
		length += ft_putchar_fd('0', 1);
		return (length);
	}
	if (data == 'x')
	{
		length += ft_putstr_fd("0x", 1);
		length += ft_putnbr_base(arg, HEXALOW);
	}
	else if (data == 'X')
	{
		length += ft_putstr_fd("0X", 1);
		length += ft_putnbr_base(arg, HEXAUP);
	}
	return (length);
}

int	handle_flags(char *flag, va_list args)
{
	int		length;
	int		i;
	long	arg_nbr;

	length = 0;
	arg_nbr = 0;
	i = 0;
	while (!ft_strchr(DATA_TYPES, flag[i]))
		i++;
	if (flag[i] == 'i' || flag[i] == 'd')
	{
		arg_nbr = va_arg(args, int);
		if ((flag[0] == '+') && (arg_nbr >= 0))
			length += apply_plus_space(&flag);
		if ((flag[0] == ' ') && (arg_nbr >= 0))
			length += apply_plus_space(&flag);
		length += ft_putnbr_base(arg_nbr, DECIMAL);
	}
	else if (flag[i] == 's' && flag[i - 1] == ' ')
		length += ft_putstr_fd(va_arg(args, char *), 1);
	else if (flag[i] == 'x' || flag[i] == 'X')
		length += apply_hash(flag[i], args);
	return (length);
}
