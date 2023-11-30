/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:35:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/30 17:50:22 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

void	draw_line(t_fdf *fdf, int x, int y)
{
	set_color(fdf, x, y);
	while ((fdf->cords->x1 > fdf->cords->x2 || fdf->cords->x1 < fdf->cords->x2)
		&& fdf->cords->y1 < fdf->cords->y2)
	{
		if ((fdf->cords->x1 < WIDTH && fdf->cords->x1 > 0)
			&& (fdf->cords->y1 > 0 && fdf->cords->y1 < HEIGHT))
			mlx_put_pixel(fdf->img, fdf->cords->x1, fdf->cords->y1, fdf->color);
		fdf->cords->x1 += fdf->cords->x_len;
		fdf->cords->y1 += fdf->cords->y_len;
		// if ((fdf->cords->x_len < fdf->cords->y_len) && (fdf->z_pos < fdf->map->matrix[y][x]))
		// 	fdf->z_pos++;
		// else if (fdf->map->matrix[y][x] < fdf->z_pos)
		// 	fdf->z_pos = fdf->map->matrix[y][x];
	}
}

void	handle_axis(t_fdf *fdf, int x, int y)
{
	if (x < fdf->map->width - 1)
	{
		set_start(fdf, x, y);
		set_end(fdf, x + 1, y);
		set_z(fdf, fdf->cords, fdf->map);
		bresenham(fdf);
		centralize(fdf);
		draw_line(fdf, x, y);
	}
	if (y < fdf->map->height - 1)
	{
		set_start(fdf, x, y);
		set_end(fdf, x, y + 1);
		set_z(fdf, fdf->cords, fdf->map);
		bresenham(fdf);
		centralize(fdf);
		draw_line(fdf, x, y);
	}
}

void	ft_render(void *param)
{
	int		x;
	int		y;
	t_fdf	*fdf;

	y = 0;
	fdf = (t_fdf *)param;
	fdf->cords->pos_x = (WIDTH / 2);
	fdf->cords->pos_y = (HEIGHT / 2);
	fdf->map->mid_w = fdf->map->width / 2;
	fdf->map->mid_h = fdf->map->height / 2;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			handle_axis(fdf, x, y);
			x++;
		}
		y++;
	}
}
