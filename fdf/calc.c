/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:18:47 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/10 17:38:29 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

void	bresenham(t_fdf *fdf)
{
	fdf->cords->z1 = fdf->map->matrix[(int)fdf->cords->y1][(int)fdf->cords->x1];
	fdf->cords->z2 = fdf->map->matrix[(int)fdf->cords->y2][(int)fdf->cords->x2];
	zoom(fdf->cords, fdf->zoom);
	isometric(&fdf->cords->x1, &fdf->cords->y1, fdf->cords->z1);
	isometric(&fdf->cords->x2, &fdf->cords->y2, fdf->cords->z2);
	fdf->cords->x_len = fdf->cords->x2 - fdf->cords->x1;
	fdf->cords->y_len = fdf->cords->y2 - fdf->cords->y1;
	if (fdf->cords->x_len > fdf->cords->y_len)
		fdf->cords->steps = fdf->cords->x_len;
	else
		fdf->cords->steps = fdf->cords->y_len;
	fdf->cords->x_len = fdf->cords->x_len / fdf->cords->steps;
	fdf->cords->y_len = fdf->cords->y_len / fdf->cords->steps;
}

void	centralize(t_fdf *fdf)
{
	fdf->cords->x1 += (WIDTH - (fdf->map->width * fdf->zoom)) / 2;
	fdf->cords->y1 += (HEIGHT - (fdf->map->height * fdf->zoom)) / 2;
	fdf->cords->x2 += (WIDTH - (fdf->map->width * fdf->zoom)) / 2;
	fdf->cords->y2 += (HEIGHT - (fdf->map->height * fdf->zoom)) / 2;
}

void	isometric(float *x, float *y, int z)
{
	//printf("z = %d\n", z);
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}
