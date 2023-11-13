/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:14:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/13 12:20:39 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

void	set_color(t_fdf *fdf, int x, int y)
{
	if (fdf->map->matrix[y][x] > 0 ||
		(y > 0 && fdf->map->matrix[y - 1][x] > 0 && fdf->cords->y_len == 0) ||
		(x > 0 && fdf->map->matrix[y][x - 1] > 0 && fdf->cords->x_len == 0))
		fdf->color = 0xff00ff77;
	else if (fdf->map->matrix[y][x] < 0 ||
		(y > 0 && fdf->map->matrix[y - 1][x] < 0 && fdf->cords->y_len == 0) ||
		(x > 0 && fdf->map->matrix[y][x - 1] < 0 && fdf->cords->x_len == 0))
		fdf->color = 0x00ff0077;
	else
		fdf->color = 0xffffff77;
}

void	zoom(t_point *cords, int zoom)
{
	cords->x1 *= zoom;
	cords->y1 *= zoom;
	cords->x2 *= zoom;
	cords->y2 *= zoom;
	cords->z1 *= zoom;
	cords->z2 *= zoom;
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
