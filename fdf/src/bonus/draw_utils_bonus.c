/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:14:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/04 11:25:39 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf_bonus.h"

void	set_color(t_fdf *fdf, int x, int y)
{
	if (fdf->map->matrix[y][x] > 0 ||
		(y > 0 && fdf->map->matrix[y - 1][x] > 0 && fdf->cords->y_len == 0) ||
		(x > 0 && fdf->map->matrix[y][x - 1] > 0 && fdf->cords->x_len == 0))
	{
		fdf->color = UP5;
	}
	else if (fdf->map->matrix[y][x] < 0 ||
		(y > 0 && fdf->map->matrix[y - 1][x] < 0 && fdf->cords->y_len == 0) ||
		(x > 0 && fdf->map->matrix[y][x - 1] < 0 && fdf->cords->x_len == 0))
		fdf->color = UP1;
	else
		fdf->color = WHITE;
}

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