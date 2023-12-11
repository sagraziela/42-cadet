/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:47:05 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/07 13:14:48 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	is_alpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	end_index;

	i = ft_strlen(argv[1]) - 1;
	end_index = 0;
	if (argc == 2)
	{
		while (i >= 0 && (argv[1][i] == ' ' || argv[1][i] == '\t'))
			i--;
		end_index = i;
		while (i >= 0 && is_alpha(argv[1][i]))
			i--;
		while (++i <= end_index)
			write(1, &argv[1][i], 1);
	}
	write(1, "\0", 1);
	return (0);
}
