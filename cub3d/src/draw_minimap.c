/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:38:20 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/20 13:25:16 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(double start_x, double start_y,
			t_mlx *mlx, unsigned int color)
{
	int	i;
	int	j;
	int	offset;

	i = 0;
	j = 0;
	start_x *= SQUARE_SIZE;
	start_y *= SQUARE_SIZE;
	while (i < SQUARE_SIZE && i + start_y < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SQUARE_SIZE && j + start_x < SCREEN_WIDTH)
		{
			offset = (((int)(start_y + i)) * (mlx->line_length))
				+ (((int)(start_x + j)) * 4);
			mlx->addr[offset] = color & 0xFF;
			mlx->addr[offset + 1] = (color >> 8) & 0xFF;
			mlx->addr[offset + 2] = (color >> 16) & 0xFF;
			mlx->addr[offset + 3] = 0xFF;
			j++;
		}
		i++;
	}
}

void	draw_rays_minimap(t_mlx *mlx)
{
	int		ray_num;
	int		current_ray;
	int		ray_color;

	ray_num = SCREEN_WIDTH;
	current_ray = 0;
	ray_color = 0x37F884;
	while (current_ray < ray_num)
	{
		calculate_rays(mlx, current_ray);
		bresenham_algorithm_minimap(mlx, ray_color);
		current_ray++;
	}
	return ;
}
