/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:40:31 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/07 14:34:37 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	check_first_str(char *str)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		counter = 0;
		while (str[j] != '\0')
		{
			if (str[i] == str[j])
				counter++;
			j++;
		}
		if (counter == 1)
			write(1, &str[i], 1);
		i++;
	}
}

void	check_second_str(char *str1, char *str2)
{
	int	i;
	int	j;
	int	x;
	int	counter;

	i = 0;
	while (str2[i] != '\0')
	{
		j = 0;
		x = 0;
		counter = 0;
		while (str1[x] != '\0' && counter == 0)
		{
			if (str1[x] == str2[i])
				counter++;
			x++;
		}
		if (counter == 0)
		{
			while (str2[j] != '\0' && counter <= 1)
			{
				if (str2[i] == str2[j])
					counter++;
				j++;
			}
			if (counter == 1)
				write(1, &str2[i], 1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		check_first_str(argv[1]);
		check_second_str(argv[1], argv[2]);
	}
	write(1, "\n", 1);
	return (0);
}

/*
void    ft_union(char *str, char *str2)
{
    int	ascii[255] = { 0 };
	int	i = 0;

	while (str[i] != '\0')
	{
		if (ascii[(int)str[i]] == 0)
		{
			write(1, &str[i], 1);
			ascii[(int)str[i]] = 1;
		}
		i++;
	}
	i = 0;
	while (str2[i] != '\0')
	{
		if (ascii[(int)str[i]] == 0)
		{
			write(1, &str[i], 1);
			ascii[(int)str[i]] = 1;
		}
		i++;
	}
} */