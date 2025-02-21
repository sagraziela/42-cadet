/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_assist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:06:47 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/13 16:23:16 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bresenham_algorithm_minimap(t_mlx *mlx, int ray_color)
{
	t_bresenham	b;

	bresenham_variable_init(mlx, &b);
	while (1)
	{
		bresenham_pixel_draw(mlx, &b, ray_color);
		if (mlx->map.matrix[b.map_y][b.map_x] == 1
			|| (b.start_x == b.end_x && b.start_y == b.end_y))
			break ;
		b.err2 = b.err * 2;
		if (b.err2 > (-b.distance_y))
		{
			b.err -= b.distance_y;
			b.start_x += b.s_x;
		}
		if (b.err2 < b.distance_x)
		{
			b.err += b.distance_x;
			b.start_y += b.s_y;
		}
		if (fabs(b.start_x - b.end_x) < 1.0 && fabs(b.start_y - b.end_y) < 1.0)
			break ;
	}
}

void	bresenham_pixel_draw(t_mlx *mlx, t_bresenham *b, int ray_color)
{
	int	screen_x;
	int	screen_y;
	int	offset;

	screen_x = (int)b->start_x;
	screen_y = (int)b->start_y;
	if ((screen_x >= 0 && screen_x < SCREEN_WIDTH)
		&& (screen_y >= 0 && screen_y < SCREEN_HEIGHT))
	{
		offset = (screen_y * mlx->line_length) + (screen_x * 4);
		mlx->addr[offset] = ray_color & 0xFF;
		mlx->addr[offset + 1] = (ray_color >> 8) & 0xFF;
		mlx->addr[offset + 2] = (ray_color >> 16) & 0xFF;
		mlx->addr[offset + 3] = 0xFF;
	}
	b->map_x = (int)(b->start_x / SQUARE_SIZE);
	b->map_y = (int)(b->start_y / SQUARE_SIZE);
	return ;
}

void	bresenham_variable_init(t_mlx *mlx, t_bresenham *b)
{
	b->start_x = (mlx->player.player_coords[0] + 0.5) * SQUARE_SIZE;
	b->start_y = (mlx->player.player_coords[1] + 0.5) * SQUARE_SIZE;
	b->end_x = mlx->player.raycast.ray_coords[0] * SQUARE_SIZE;
	b->end_y = mlx->player.raycast.ray_coords[1] * SQUARE_SIZE;
	b->distance_x = fabs(b->end_x - b->start_x);
	b->distance_y = fabs(b->end_y - b->start_y);
	if (b->start_x < b->end_x)
		b->s_x = 1;
	else
		b->s_x = -1;
	if (b->start_y < b->end_y)
		b->s_y = 1;
	else
		b->s_y = -1;
	b->err = b->distance_x - b->distance_y;
}
