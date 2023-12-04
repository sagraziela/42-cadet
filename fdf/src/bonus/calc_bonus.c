/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:18:47 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/04 18:44:10 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf_bonus.h"

void	set_steps(t_fdf *fdf, float x_len, float y_len)
{
	if (x_len < 0)
		x_len *= -1;
	if (y_len < 0)
		y_len *= -1;
	if (x_len > y_len)
		fdf->cords->steps = x_len;
	else
		fdf->cords->steps = y_len;
}

void	scale_cords(t_fdf *fdf)
{
	fdf->cords->x1 -= fdf->map->mid_w;
	fdf->cords->y1 -= fdf->map->mid_h;
	fdf->cords->x2 -= fdf->map->mid_w;
	fdf->cords->y2 -= fdf->map->mid_h;
	zoom(fdf, &fdf->zoom);
}

void	bresenham(t_fdf *fdf)
{
	scale_cords(fdf);
	isometric(fdf, &fdf->cords->x1, &fdf->cords->y1, fdf->cords->z1);
	isometric(fdf, &fdf->cords->x2, &fdf->cords->y2, fdf->cords->z2);
	fdf->cords->x_len = fdf->cords->x2 - fdf->cords->x1;
	fdf->cords->y_len = fdf->cords->y2 - fdf->cords->y1;
	set_steps(fdf, fdf->cords->x_len, fdf->cords->y_len);
	fdf->cords->x_len = fdf->cords->x_len / fdf->cords->steps;
	fdf->cords->y_len = fdf->cords->y_len / fdf->cords->steps;
}

void	centralize(t_fdf *fdf)
{
	mlx_set_window_pos(fdf->mlx, fdf->cords->pos_x, fdf->cords->pos_y);
	fdf->cords->x1 += fdf->cords->pos_x;
	fdf->cords->y1 += fdf->cords->pos_y;
	fdf->cords->x2 += fdf->cords->pos_x;
	fdf->cords->y2 += fdf->cords->pos_y;
}

void	isometric(t_fdf *fdf, float *x, float *y, int z)
{
	*x = (*x - *y) * cos(fdf->map->angle);
	*y = (*x + *y) * sin(fdf->map->angle) - z;
}
