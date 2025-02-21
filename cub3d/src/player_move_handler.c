/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:45:49 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/20 13:42:01 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
		exit_cub(mlx);
	else if (keysym == 119 || keysym == XK_Up)
		player_move_forward(mlx);
	else if (keysym == 115 || keysym == XK_Down)
		player_move_backward(mlx);
	else if (keysym == 97)
		player_move_left(mlx);
	else if (keysym == 100)
		player_move_right(mlx);
	else if (keysym == XK_Right)
		player_turn_right(mlx);
	else if (keysym == XK_Left)
		player_turn_left(mlx);
	if (mlx->player.player_angle[0] < 0)
		mlx->player.player_angle[0] += 2 * M_PI;
	if (mlx->player.player_angle[0] > 2 * M_PI)
		mlx->player.player_angle[0] -= 2 * M_PI;
	return (0);
}

void	player_move_forward(t_mlx *mlx)
{
	mlx->player.new_x = cos(atan2(mlx->player.player_vector[1],
				mlx->player.player_vector[0])) * MOVEMENT_SPEED;
	mlx->player.new_y = sin(atan2(mlx->player.player_vector[1],
				mlx->player.player_vector[0])) * MOVEMENT_SPEED;
	if ((mlx->map.matrix[(int)(mlx->player.player_coords[1]
				+ mlx->player.new_y)]
		[(int)(mlx->player.player_coords[0] + mlx->player.new_x)] != 1)
			&&
		(mlx->map.matrix[(int)(mlx->player.player_coords[1] + 0.8
			+ mlx->player.new_y)]
			[(int)(mlx->player.player_coords[0] + mlx->player.new_x)] != 1)
			&&
		(mlx->map.matrix[(int)(mlx->player.player_coords[1]
			+ mlx->player.new_y)]
			[(int)(mlx->player.player_coords[0]
				+ 0.8 + mlx->player.new_x)] != 1)
			&&
		(mlx->map.matrix[(int)(mlx->player.player_coords[1] + 0.8
			+ mlx->player.new_y)]
			[(int)(mlx->player.player_coords[0]
				+ 0.8 + mlx->player.new_x)] != 1))
	{
		mlx->player.player_coords[0] += mlx->player.new_x;
		mlx->player.player_coords[1] += mlx->player.new_y;
	}
}

void	player_move_backward(t_mlx *mlx)
{
	mlx->player.new_x = cos(atan2(mlx->player.player_vector[1],
				mlx->player.player_vector[0])) * -MOVEMENT_SPEED;
	mlx->player.new_y = sin(atan2(mlx->player.player_vector[1],
				mlx->player.player_vector[0])) * -MOVEMENT_SPEED;
	if (mlx->map.matrix[(int)(mlx->player.player_coords[1] + mlx->player.new_y)]
		[(int)(mlx->player.player_coords[0] + mlx->player.new_x)] != 1
			&&
		mlx->map.matrix[(int)(mlx->player.player_coords[1] + 0.8
			+ mlx->player.new_y)]
			[(int)(mlx->player.player_coords[0] + mlx->player.new_x)] != 1
			&&
		mlx->map.matrix[(int)(mlx->player.player_coords[1]
			+ mlx->player.new_y)]
			[(int)(mlx->player.player_coords[0] + 0.8 + mlx->player.new_x)] != 1
			&&
		mlx->map.matrix[(int)(mlx->player.player_coords[1] + 0.8
			+ mlx->player.new_y)]
			[(int)(mlx->player.player_coords[0]
				+ 0.8 + mlx->player.new_x)] != 1)
	{
		mlx->player.player_coords[0] += mlx->player.new_x;
		mlx->player.player_coords[1] += mlx->player.new_y;
	}
}

void	player_move_left(t_mlx *mlx)
{
	mlx->player.new_x = cos(atan2(mlx->player.player_vector[1],
				mlx->player.player_vector[0]) - (M_PI / 2)) * MOVEMENT_SPEED;
	mlx->player.new_y = sin(atan2(mlx->player.player_vector[1],
				mlx->player.player_vector[0]) - (M_PI / 2)) * MOVEMENT_SPEED;
	if ((mlx->map.matrix[(int)(mlx->player.player_coords[1]
				+ mlx->player.new_y)]
		[(int)(mlx->player.player_coords[0] + mlx->player.new_x)] != 1)
			&&
		(mlx->map.matrix[(int)(mlx->player.player_coords[1] + 0.8
			+ mlx->player.new_y)]
		[(int)(mlx->player.player_coords[0] + mlx->player.new_x)] != 1)
			&&
		(mlx->map.matrix[(int)(mlx->player.player_coords[1]
			+ mlx->player.new_y)]
		[(int)(mlx->player.player_coords[0] + 0.8 + mlx->player.new_x)] != 1)
			&&
		(mlx->map.matrix[(int)(mlx->player.player_coords[1] + 0.8
			+ mlx->player.new_y)]
		[(int)(mlx->player.player_coords[0] + 0.8 + mlx->player.new_x)] != 1))
	{
		mlx->player.player_coords[0] += mlx->player.new_x;
		mlx->player.player_coords[1] += mlx->player.new_y;
	}
}

void	player_move_right(t_mlx *mlx)
{
	mlx->player.new_x = cos(atan2(mlx->player.player_vector[1],
				mlx->player.player_vector[0]) + (M_PI / 2)) * MOVEMENT_SPEED;
	mlx->player.new_y = sin(atan2(mlx->player.player_vector[1],
				mlx->player.player_vector[0]) + (M_PI / 2)) * MOVEMENT_SPEED;
	if ((mlx->map.matrix[(int)(mlx->player.player_coords[1]
				+ mlx->player.new_y)]
		[(int)(mlx->player.player_coords[0] + mlx->player.new_x)] != 1)
			&&
		(mlx->map.matrix[(int)(mlx->player.player_coords[1]
				+ 0.8 + mlx->player.new_y)]
			[(int)(mlx->player.player_coords[0] + mlx->player.new_x)] != 1)
			&&
		(mlx->map.matrix[(int)(mlx->player.player_coords[1]
			+ mlx->player.new_y)]
			[(int)(mlx->player.player_coords[0]
			+ 0.8 + mlx->player.new_x)] != 1)
			&&
		(mlx->map.matrix[(int)(mlx->player.player_coords[1]
				+ 0.8 + mlx->player.new_y)]
			[(int)(mlx->player.player_coords[0]
				+ 0.8 + mlx->player.new_x)] != 1))
	{
		mlx->player.player_coords[0] += mlx->player.new_x;
		mlx->player.player_coords[1] += mlx->player.new_y;
	}
}
