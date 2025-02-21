/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_camera_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:00:23 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/13 16:19:27 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_turn_right(t_mlx *mlx)
{
	mlx->player.old_dir_x = mlx->player.player_vector[0];
	mlx->player.player_vector[0] = mlx->player.player_vector[0]
		* cos(ROTATION_SPEED) - mlx->player.player_vector[1]
		* sin(ROTATION_SPEED);
	mlx->player.player_vector[1] = mlx->player.old_dir_x
		* sin(ROTATION_SPEED) + mlx->player.player_vector[1]
		* cos(ROTATION_SPEED);
	mlx->player.old_plane_x = mlx->player.player_plane[0];
	mlx->player.player_plane[0] = mlx->player.player_plane[0]
		* cos(ROTATION_SPEED) - mlx->player.player_plane[1]
		* sin(ROTATION_SPEED);
	mlx->player.player_plane[1] = mlx->player.old_plane_x
		* sin(ROTATION_SPEED) + mlx->player.player_plane[1]
		* cos(ROTATION_SPEED);
	mlx->player.player_angle[0] = atan2(mlx->player.player_vector[1],
			mlx->player.player_vector[0]);
}

void	player_turn_left(t_mlx *mlx)
{
	mlx->player.old_dir_x = mlx->player.player_vector[0];
	mlx->player.player_vector[0] = mlx->player.player_vector[0]
		* cos(-ROTATION_SPEED) - mlx->player.player_vector[1]
		* sin(-ROTATION_SPEED);
	mlx->player.player_vector[1] = mlx->player.old_dir_x
		* sin(-ROTATION_SPEED) + mlx->player.player_vector[1]
		* cos(-ROTATION_SPEED);
	mlx->player.old_plane_x = mlx->player.player_plane[0];
	mlx->player.player_plane[0] = mlx->player.player_plane[0]
		* cos(-ROTATION_SPEED) - mlx->player.player_plane[1]
		* sin(-ROTATION_SPEED);
	mlx->player.player_plane[1] = mlx->player.old_plane_x
		* sin(-ROTATION_SPEED) + mlx->player.player_plane[1]
		* cos(-ROTATION_SPEED);
	mlx->player.player_angle[0] = atan2(mlx->player.player_vector[1],
			mlx->player.player_vector[0]);
}
