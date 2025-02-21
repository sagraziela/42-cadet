/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_assist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:05:02 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/18 15:28:42 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_rays_var_init1(t_mlx *mlx, int current_ray)
{
	mlx->player.player_camera_x = 2 * current_ray / (double)SCREEN_WIDTH - 1;
	mlx->player.raycast.ray_dir_vector[0] = mlx->player.player_vector[0]
		+ mlx->player.player_plane[0] * mlx->player.player_camera_x;
	mlx->player.raycast.ray_dir_vector[1] = mlx->player.player_vector[1]
		+ mlx->player.player_plane[1] * mlx->player.player_camera_x;
	mlx->player.raycast.ray_x = (mlx->player.player_coords[0] + 0.5);
	mlx->player.raycast.ray_y = (mlx->player.player_coords[1] + 0.5);
	mlx->player.raycast.map_x = (int)mlx->player.raycast.ray_x;
	mlx->player.raycast.map_y = (int)mlx->player.raycast.ray_y;
	if (mlx->player.raycast.ray_dir_vector[0] == 0)
		mlx->player.raycast.dist_to_next_x = 1e30;
	else
		mlx->player.raycast.dist_to_next_x = fabs(1
				/ mlx->player.raycast.ray_dir_vector[0]);
	if (mlx->player.raycast.ray_dir_vector[1] == 0)
		mlx->player.raycast.dist_to_next_y = 1e30;
	else
		mlx->player.raycast.dist_to_next_y = fabs(1
				/ mlx->player.raycast.ray_dir_vector[1]);
}

void	calculate_rays_var_init2(t_mlx *mlx)
{
	if (mlx->player.raycast.ray_dir_vector[0] < 0)
	{
		mlx->player.raycast.step_x = -1;
		mlx->player.raycast.dist_to_closest_x
			= (mlx->player.raycast.ray_x - mlx->player.raycast.map_x)
			* mlx->player.raycast.dist_to_next_x;
	}
	else
	{
		mlx->player.raycast.step_x = 1;
		mlx->player.raycast.dist_to_closest_x
			= (mlx->player.raycast.map_x + 1.0 - mlx->player.raycast.ray_x)
			* mlx->player.raycast.dist_to_next_x;
	}
}

void	calculate_rays_var_init3(t_mlx *mlx)
{
	if (mlx->player.raycast.ray_dir_vector[1] < 0)
	{
		mlx->player.raycast.step_y = -1;
		mlx->player.raycast.dist_to_closest_y
			= (mlx->player.raycast.ray_y - mlx->player.raycast.map_y)
			* mlx->player.raycast.dist_to_next_y;
	}
	else
	{
		mlx->player.raycast.step_y = 1;
		mlx->player.raycast.dist_to_closest_y
			= (mlx->player.raycast.map_y + 1.0 - mlx->player.raycast.ray_y)
			* mlx->player.raycast.dist_to_next_y;
	}
}

void	calculate_rays_var_init4(t_mlx *mlx)
{
	while ((mlx->map.matrix[mlx->player.raycast.map_y]
			[mlx->player.raycast.map_x] != 1))
	{
		if (mlx->player.raycast.dist_to_closest_x
			< mlx->player.raycast.dist_to_closest_y)
		{
			mlx->player.raycast.dist_to_closest_x
				+= mlx->player.raycast.dist_to_next_x;
			mlx->player.raycast.map_x += mlx->player.raycast.step_x;
			mlx->side = 0;
		}
		else
		{
			mlx->player.raycast.dist_to_closest_y
				+= mlx->player.raycast.dist_to_next_y;
			mlx->player.raycast.map_y += mlx->player.raycast.step_y;
			mlx->side = 1;
		}
	}
}
