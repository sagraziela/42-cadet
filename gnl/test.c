/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:16:13 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/11 17:01:34 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int	main(void)
{
	static t_list	list;
	int				fd;
	char			buff[10];
	int				chars_read;

	fd = open("file.txt", O_RDONLY);
	chars_read = read(fd, buff, 1024);
	while (read(fd, buff, 1024))
	{
		if (buff[chars_read] == '\n')
			break ;
		buff[chars_read] = '\0';
		printf("buff >> %s\n", buff);
	}
	return (0);
}
