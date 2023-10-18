/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:23:59 by gde-souz          #+#    #+#             */
/*   Updated: 2023/10/18 13:00:44 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

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
	return (height);
}

void	fill_matrix(char *fd_line, int *matrix_line)
{
	int		i;
	char	**splited;

	i = 0;
	splited = ft_split(fd_line, ' ');
	while (splited[i])
	{
		matrix_line[i] = atoi(splited[i]);
		free(splited[i]);
		i++;
	}
	free(splited);
	matrix_line[i] = '\0';
}

int	read_map(char *file, t_struct *fdf)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fdf->height = get_height(file);
	fdf->matrix = (int **)malloc(sizeof(int *) * (fdf->height + 1));
	if (!fdf->matrix)
		return (0);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	fdf->width = count_words(line);
	while (i < fdf->height)
	{
		fdf->matrix[i] = (int *)malloc(sizeof(int) * (fdf->width + 1));
		if (!fdf->matrix)
			return (0);
		fill_matrix(line, fdf->matrix[i]);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	fdf->matrix[i] = NULL;
	close(fd);
	return (fdf->height * fdf->width);
}
