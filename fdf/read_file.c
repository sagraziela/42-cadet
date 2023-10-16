/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2023/10/16 18:02:44 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	count_words(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0')
			counter++;
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (counter);
}

int	get_height(char *file_name)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	//printf("%d\n", width);
	return (height);
}

int	get_width(char *file_name)
{
	int		fd;
	int		width;
	char	*line;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	width = count_words(line);
	free(line);
	close(fd);
	//printf("%d\n", width);
	return (width);
}

int	fill_line(char *fd_line, int *matrix_line, int length)
{
	int	i;

	matrix_line = (int *)malloc(sizeof(int) * (length + 1));
	if (!matrix_line)
		return (0);
	while (fd_line != '\0')
	{
		matrix_line[i] = atoi(fd_line[i]); //trocar pela minha atoi();
		i++;
	}
}

int	read_map(char *file, t_struct *fdf)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fdf->height = get_height(file);
	fdf->length = get_width(file);
	fdf->matrix = (int **)malloc(sizeof(int *) * fdf->height + 1);
	if (!fdf->matrix)
		return (0);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_line(&line, &fdf->matrix[i], fdf->length);
		free(line);
		line = get_next_line(fd);
		i++;
	}
}
