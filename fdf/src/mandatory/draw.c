/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:35:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/04 18:34:03 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	draw_line(t_fdf *fdf, int x, int y)
{
	unsigned int	i;

	i = 0;
	while (i < fdf->cords->steps)
	{
		set_color(fdf, x, y);
		if ((fdf->cords->x1 < WIDTH && fdf->cords->x1 > MENU_WIDTH
				&& fdf->cords->x1 > 0)
			&& (fdf->cords->y1 > 0 && fdf->cords->y1 < HEIGHT))
			mlx_put_pixel(fdf->img, fdf->cords->x1, fdf->cords->y1, fdf->color);
		fdf->cords->x1 += fdf->cords->x_len;
		fdf->cords->y1 += fdf->cords->y_len;
		i++;
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

void	display_menu(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < MENU_WIDTH)
		{
			if (x >= MENU_WIDTH - 2)
				mlx_put_pixel(fdf->img, x, y, 0x00000077);
			else
				mlx_put_pixel(fdf->img, x, y, 0x19197077);
			x++;
		}
		y++;
	}
	mlx_put_string(fdf->mlx, "INSTRUCTIONS", 100, 30);
	mlx_put_string(fdf->mlx, "Mouse SCROLL:", 20, 100);
	mlx_put_string(fdf->mlx, "zoom in/out;", 70, 120);
	mlx_put_string(fdf->mlx, "+ and -:", 20, 160);
	mlx_put_string(fdf->mlx, "changes Z scale;", 70, 180);
	mlx_put_string(fdf->mlx, "Arrow-UP/DOWN:", 20, 220);
	mlx_put_string(fdf->mlx, "changes isometric angle;", 70, 240);
}

void	ft_render(void *param)
{
	int		x;
	int		y;
	t_fdf	*fdf;

	y = 0;
	fdf = (t_fdf *)param;
	fdf->map->mid_w = fdf->map->width / 2;
	fdf->map->mid_h = fdf->map->height / 2;
	display_menu(fdf);
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
