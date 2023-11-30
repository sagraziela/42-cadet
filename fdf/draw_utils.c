/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:14:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/30 17:43:17 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

int	set_gradient(int z, t_fdf *fdf)
{
	double	percentage;
	double	placement;
	double	distance;

	placement = fdf->z_pos - 0;
	distance = z - 0;
	printf("z_pos: %d\n", fdf->z_pos);
	printf("placement: %f	||	distance: %f\n", placement, distance);
	if (distance == 0)
		percentage = 1.0;
	else
		percentage = placement / distance;
	if (percentage < 0.2)
		return (UP1);
	else if (percentage < 0.4)
		return (UP2);
	else if (percentage < 0.6)
		return (UP3);
	else if (percentage < 0.8)
		return (UP4);
	else
		return (UP5);
}

void	set_color(t_fdf *fdf, int x, int y)
{
	int	z_value;

	z_value = fdf->map->matrix[y][x];
	if (fdf->map->matrix[y][x] > 0 ||
		(y > 0 && fdf->map->matrix[y - 1][x] > 0 && fdf->cords->y_len == 0) ||
		(x > 0 && fdf->map->matrix[y][x - 1] > 0 && fdf->cords->x_len == 0))
	{
		fdf->color = set_gradient(z_value, fdf);
	}
	else if (fdf->map->matrix[y][x] < 0 ||
		(y > 0 && fdf->map->matrix[y - 1][x] < 0 && fdf->cords->y_len == 0) ||
		(x > 0 && fdf->map->matrix[y][x - 1] < 0 && fdf->cords->x_len == 0))
		fdf->color = set_gradient(z_value, fdf);
	else
		fdf->color = 0xffffff77;
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
