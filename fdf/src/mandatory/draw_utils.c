/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:14:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/07 14:02:44 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	set_start(t_fdf *fdf, int x1, int y1)
{
	fdf->cords->x1 = x1;
	fdf->cords->y1 = y1;
}

void	set_end(t_fdf *fdf, int x2, int y2)
{
	fdf->cords->x2 = x2;
	fdf->cords->y2 = y2;
}

void	set_z(t_fdf *fdf, t_point *cords, t_map *map)
{
	fdf->cords->z1 = map->matrix[(int)cords->y1][(int)cords->x1] * fdf->z_scale;
	fdf->cords->z2 = map->matrix[(int)cords->y2][(int)cords->x2] * fdf->z_scale;
}

void	zoom(t_fdf *fdf, int *zoom)
{
	if (*zoom == 0)
	{
		while ((*zoom * fdf->map->height <= fdf->cords->pos_y)
			&& (*zoom * fdf->map->width <= fdf->cords->pos_x))
			*zoom += 1;
	}
	fdf->cords->x1 *= *zoom;
	fdf->cords->y1 *= *zoom;
	fdf->cords->x2 *= *zoom;
	fdf->cords->y2 *= *zoom;
}
