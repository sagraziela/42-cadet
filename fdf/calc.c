/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:18:47 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/23 15:41:23 by gde-souz         ###   ########.fr       */
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
	fdf->cords->x1 -= (fdf->map->width / 2);
	fdf->cords->y1 -= (fdf->map->height / 2);
	fdf->cords->x2 -= (fdf->map->width / 2);
	fdf->cords->y2 -= (fdf->map->height / 2);
	zoom(fdf->cords, fdf->zoom);
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
	//printf("pos_x: %d | pos_y: %d\n", fdf->cords->pos_x, fdf->cords->pos_y);
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

// void	centralize_map_center(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i <= map->height)
// 	{
// 		j = 0;
// 		while (j <= map->width)
// 		{
// 			map->matrix[i][j] -= map
// 		}
// 	}
// }
