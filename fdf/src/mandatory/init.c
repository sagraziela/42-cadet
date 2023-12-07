/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:31:26 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/07 14:02:50 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	init_fdf_variables(t_fdf *fdf, char *map_name, int n_args)
{
	if (map_name != NULL && map_name)
		fdf->name = ft_strjoin("FDF - ", ft_strrchr(map_name, '/'));
	else
		fdf->name = NULL;
	fdf->argc = n_args;
	fdf->zoom = 0;
	fdf->color = 0;
	fdf->z_scale = 1;
	fdf->z_max = 100;
	fdf->z_min = -100;
	fdf->z_pos = 0;
	fdf->z_highest = 0;
}

t_map	*map_init(t_map *map)
{
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->angle = 0.8;
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
	cords->pos_x = ((WIDTH + MENU_WIDTH) / 2);
	cords->pos_y = (HEIGHT / 2);
	return (cords);
}
