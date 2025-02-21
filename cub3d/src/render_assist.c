/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:42:14 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/18 15:13:30 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ray(t_mlx *mlx, int current_ray)
{
	t_texture		img;

	img = render_ray_assist1(mlx);
	render_ray_assist2(mlx, &img);
	img.texture_position = (mlx->player.raycast.first_wall_pixel - SCREEN_HEIGHT
			/ 2 + mlx->player.raycast.line_height / 2)
		* mlx->player.raycast.texture_step;
	while (mlx->player.raycast.current_wall_pixel
		<= mlx->player.raycast.last_wall_pixel)
	{
		img.texture_y = (int)img.texture_position & (TEXTURE_HEIGHT - 1);
		img.texture_position += mlx->player.raycast.texture_step;
		mlx->player.raycast.ray_color
			= get_pixel_img(&img, img.texture_x, img.texture_y);
		put_pixel_img(mlx, current_ray,
			mlx->player.raycast.current_wall_pixel,
			mlx->player.raycast.ray_color);
		mlx->player.raycast.current_wall_pixel++;
	}
}

unsigned int	get_pixel_img(t_texture *img, int x, int y)
{
	return (*(unsigned int *)((img->addr
			+ (y * img->line_length) + (x * img->bits_per_pixel / 8))));
}

t_texture	render_ray_assist1(t_mlx *mlx)
{
	t_texture	*img;

	if (mlx->side == 0)
	{
		mlx->player.raycast.wall_x = mlx->player.player_coords[1] - 0.5
			+ mlx->player.raycast.ray_truedist
			* mlx->player.raycast.ray_dir_vector[1];
		if (mlx->player.raycast.ray_dir_vector[0] < 0)
			img = &mlx->e_wall_texture;
		else
			img = &mlx->w_wall_texture;
	}
	else
	{
		if (mlx->player.raycast.ray_dir_vector[1] > 0)
			img = &mlx->s_wall_texture;
		else
			img = &mlx->n_wall_texture;
		mlx->player.raycast.wall_x = mlx->player.player_coords[0] - 0.5
			+ mlx->player.raycast.ray_truedist
			* mlx->player.raycast.ray_dir_vector[0];
	}
	return (*img);
}

void	render_ray_assist2(t_mlx *mlx, t_texture *img)
{
	mlx->player.raycast.wall_x -= floor((mlx->player.raycast.wall_x));
	img->texture_x = mlx->player.raycast.wall_x * (double)TEXTURE_WIDTH;
	if (mlx->side == 0 && mlx->player.raycast.ray_dir_vector[0] > 0)
		img->texture_x = TEXTURE_WIDTH - img->texture_x - 1;
	if (mlx->side == 1 && mlx->player.raycast.ray_dir_vector[1] < 0)
		img->texture_x = TEXTURE_WIDTH - img->texture_x - 1;
	mlx->player.raycast.line_height
		= (int)(SCREEN_HEIGHT / mlx->player.raycast.ray_truedist);
	mlx->player.raycast.first_wall_pixel = -mlx->player.raycast.line_height
		/ 2 + SCREEN_HEIGHT / 2;
	if (mlx->player.raycast.first_wall_pixel < 0)
		mlx->player.raycast.first_wall_pixel = 0;
	mlx->player.raycast.last_wall_pixel = mlx->player.raycast.line_height
		/ 2 + SCREEN_HEIGHT / 2;
	if (mlx->player.raycast.last_wall_pixel >= SCREEN_HEIGHT)
		mlx->player.raycast.last_wall_pixel = SCREEN_HEIGHT - 1;
	mlx->player.raycast.current_wall_pixel
		= mlx->player.raycast.first_wall_pixel;
	mlx->player.raycast.texture_step = 1.0 * TEXTURE_HEIGHT
		/ mlx->player.raycast.line_height;
}

void	render_sky_floor_assist(t_mlx *mlx, int screen_x,
		int screen_y, unsigned int color)
{
	int	offset;

	offset = ((screen_y) * mlx->line_length) + ((screen_x) * 4);
	mlx->addr[offset] = color & 0xFF;
	mlx->addr[offset + 1] = (color >> 8) & 0xFF;
	mlx->addr[offset + 2] = (color >> 16) & 0xFF;
	mlx->addr[offset + 3] = 0xFF;
}
