/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:13:25 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/22 13:32:43 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./gnl.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 2)
	{
		line = NULL;
		fd = open(argv[1], O_RDONLY);
		if (fd <= 0)
			return (1);
		while (1)
		{
			line = get_next_line(fd);
			if (!line)
				return (0);
			printf("%s", line);
			free(line);
		}
		return (0);
	}
	return (1);
}