/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:18:47 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/13 16:04:37 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

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

void	bresenham(t_fdf *fdf)
{
	fdf->cords->z1 = fdf->map->matrix[(int)fdf->cords->y1][(int)fdf->cords->x1];
	fdf->cords->z2 = fdf->map->matrix[(int)fdf->cords->y2][(int)fdf->cords->x2];
	zoom(fdf->cords, fdf->zoom);
	isometric(&fdf->cords->x1, &fdf->cords->y1, fdf->cords->z1);
	isometric(&fdf->cords->x2, &fdf->cords->y2, fdf->cords->z2);
	fdf->cords->x_len = fdf->cords->x2 - fdf->cords->x1;
	fdf->cords->y_len = fdf->cords->y2 - fdf->cords->y1;
	set_steps(fdf, fdf->cords->x_len, fdf->cords->y_len);
	fdf->cords->x_len = fdf->cords->x_len / fdf->cords->steps;
	fdf->cords->y_len = fdf->cords->y_len / fdf->cords->steps;
}

void	centralize(t_fdf *fdf)
{
	fdf->cords->x1 += (WIDTH - (fdf->map->width * fdf->zoom) / 2) / 2;
	fdf->cords->y1 += (HEIGHT - (fdf->map->height * fdf->zoom) / 2) / 2;
	fdf->cords->x2 += (WIDTH - (fdf->map->width * fdf->zoom) / 2) / 2;
	fdf->cords->y2 += (HEIGHT - (fdf->map->height * fdf->zoom) / 2) / 2;
}

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}
