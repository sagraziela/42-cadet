/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:31:26 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/04 14:54:15 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	get_highest_z(t_fdf *fdf)
{
	int	i;
	int	j;
	int	z_highest;

	i = 0;
	z_highest = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			if (fdf->map->matrix[i][j] > z_highest)
				z_highest = fdf->map->matrix[i][j];
			j++;
		}
		i++;
	}
	return (z_highest);
}

void	init_fdf_variables(t_fdf *fdf, char *map_name, int n_args)
{
	if (map_name != NULL)
		fdf->name = ft_strjoin("FDF - ", ft_strrchr(map_name, '/'));
	else
		fdf->name = NULL;
	fdf->argc = n_args;
	fdf->zoom = 0;
	fdf->color = 0;
	fdf->z_scale = 10;
	fdf->z_max = 1000;
	fdf->z_min = -1000;
	fdf->z_pos = 0;
	fdf->z_highest = 0;
}

t_map	*map_init(t_map *map)
{
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->angle = 0.8;
	// map->min_angle = 0.0;
	// map->max_angle = 1.2;
	map->matrix = NULL;
	return (map);
}

t_point	*cords_init(t_point *cords)
{
	cords = malloc(sizeof(t_point));
	if (!cords)
		return (NULL);
	cords->x1 = 0;
	cords->y1 = 0;
	cords->x2 = 0;
	cords->y2 = 0;
	cords->steps = 0;
	cords->pos_x = 0;
	cords->pos_y = 0;
	return (cords);
}
