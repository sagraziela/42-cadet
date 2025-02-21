/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:39:24 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/13 16:20:33 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	south_player_spawn(t_mlx *mlx, int i, int j)
{
	mlx->player.player_coords[0] = j;
	mlx->player.player_coords[1] = i;
	mlx->player.player_angle[0] = M_PI / 2;
	mlx->player.player_vector[0] = 0;
	mlx->player.player_vector[1] = 1;
	return ;
}

void	north_player_spawn(t_mlx *mlx, int i, int j)
{
	mlx->player.player_coords[0] = j;
	mlx->player.player_coords[1] = i;
	mlx->player.player_angle[0] = (3 * M_PI) / 2;
	mlx->player.player_vector[0] = 0;
	mlx->player.player_vector[1] = -1;
	return ;
}

void	east_player_spawn(t_mlx *mlx, int i, int j)
{
	mlx->player.player_coords[0] = j;
	mlx->player.player_coords[1] = i;
	mlx->player.player_angle[0] = 2 * M_PI;
	mlx->player.player_vector[0] = 1;
	mlx->player.player_vector[1] = 0;
	return ;
}

void	west_player_spawn(t_mlx *mlx, int i, int j)
{
	mlx->player.player_coords[0] = j;
	mlx->player.player_coords[1] = i;
	mlx->player.player_angle[0] = M_PI;
	mlx->player.player_vector[0] = -1;
	mlx->player.player_vector[1] = 0;
	return ;
}
