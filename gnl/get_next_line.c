/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:10:00 by gde-souz          #+#    #+#             */
/*   Updated: 2023/08/11 18:14:29 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	**list;
	int				file;
	size_t			rd;
	char			*buffer[BUFF_SIZE];

	list = NULL;
	file = open(fd, O_RDONLY);
	if (file == -1)
		return (NULL);
	rd = read(file, buffer, BUFF_SIZE);
	while (read(file, buffer, BUFF_SIZE))
	{
		buffer[rd] = '\0';
		ft_lstadd(list, buffer);
		printf("%s", buffer);
	}
	close(file);
	return (*buffer);
}

int	main(void)
{
	get_next_line(9);
}
