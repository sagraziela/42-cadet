/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:48:25 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/16 15:09:27 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	search_and_replace(char *str, char letter, char new_letter)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == letter)
			write(1, &new_letter, 1);
		else
			write(1, &str[i], 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 4 && !argv[2][1] && !argv[3][1])
		search_and_replace(argv[1], argv[2][0], argv[3][0]);
	write(1, "\n", 1);
	return (0);
}
