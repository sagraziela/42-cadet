/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:29:08 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/16 18:25:57 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static t_bool	ft_isnumeric(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
	}
	return (TRUE);
}

static long	ft_atoi(const char *nptr)
{
	int		i;
	long	sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if ((nptr[i] == '+'))
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	return (res * sign);
}

static t_bool	args_are_valid(int argc, char **argv)
{
	int		i;
	long	temp;

	i = 0;
	while (++i < argc)
	{
		temp = ft_atoi(argv[i]);
		if (!ft_isnumeric(argv[i]) || (temp > INT_MAX || temp < 0))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	handle_args(int argc, char *argv[], t_dinner **dinner)
{
	if ((argc != 5 && argc != 6) || !args_are_valid(argc, argv))
		return (FALSE);
	(*dinner)->philos_num = ft_atoi(argv[1]);
	(*dinner)->time_to_die = ft_atoi(argv[2]) * 1000;
	(*dinner)->time_to_eat = ft_atoi(argv[3]) * 1000;
	(*dinner)->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		(*dinner)->total_meals = ft_atoi(argv[5]);
		(*dinner)->infinite_dinner = FALSE;
	}
	else
	{
		(*dinner)->total_meals = 0;
		(*dinner)->infinite_dinner = TRUE;
	}
	return (TRUE);
}
