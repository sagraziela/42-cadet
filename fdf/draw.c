/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:35:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/09 16:33:12 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

void	draw_line(t_fdf *fdf, int x, int y)
{
	int	i;

	set_color(fdf, x, y);
	i = 0;
	while (fdf->cords->x1 <= fdf->cords->x2 && fdf->cords->y1 <= fdf->cords->y2)
	{
		mlx_put_pixel(fdf->img, fdf->cords->x1, fdf->cords->y1, fdf->color);
		fdf->cords->x1 += fdf->cords->x_len;
		fdf->cords->y1 += fdf->cords->y_len;
	}
}

void	handle_x(t_fdf *fdf, int x, int y)
{
	set_start(fdf, x, y);
	set_end(fdf, x + 1, y);
	bresenham(fdf);
	set_z(fdf, x, y);
	zoom(fdf->cords, fdf->zoom);
	draw_line(fdf, x, y);
}

void	handle_y(t_fdf *fdf, int x, int y)
{
	set_start(fdf, x, y);
	set_end(fdf, x, y + 1);
	bresenham(fdf);
	set_z(fdf, x, y);
	zoom(fdf->cords, fdf->zoom);
	draw_line(fdf, x, y);
}

void	close_lines(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map->width - 1)
	{
		handle_x(fdf, i, fdf->map->height - 1);
		i++;
	}
	i = 0;
	while (i < fdf->map->height - 1)
	{
		handle_y(fdf, fdf->map->width - 1, i);
		i++;
	}
}

void	ft_render(void *param)
{
	int		x;
	int		y;
	t_fdf	*fdf;

	y = 0;
	fdf = (t_fdf *)param;
	while (y < fdf->map->height - 1)
	{
		x = 0;
		while (x < fdf->map->width - 1)
		{
			handle_x(fdf, x, y);
			handle_y(fdf, x, y);
			x++;
		}
		y++;
	}
	close_lines(fdf);
}

//cc ./*.c ./gnl/*.c ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
