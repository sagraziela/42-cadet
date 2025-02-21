/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:40:59 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/20 13:26:04 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	calculate_rays(t_mlx *mlx, int current_ray)
{
	calculate_rays_var_init1(mlx, current_ray);
	calculate_rays_var_init2(mlx);
	calculate_rays_var_init3(mlx);
	calculate_rays_var_init4(mlx);
	if (mlx->side == 0)
		mlx->player.raycast.ray_truedist
			= (mlx->player.raycast.dist_to_closest_x
				- mlx->player.raycast.dist_to_next_x);
	else
		mlx->player.raycast.ray_truedist
			= (mlx->player.raycast.dist_to_closest_y
				- mlx->player.raycast.dist_to_next_y);
	mlx->player.raycast.ray_coords[0] = mlx->player.raycast.ray_x
		+ (mlx->player.raycast.ray_dir_vector[0]
			* mlx->player.raycast.ray_truedist);
	mlx->player.raycast.ray_coords[1] = mlx->player.raycast.ray_y
		+ (mlx->player.raycast.ray_dir_vector[1]
			* mlx->player.raycast.ray_truedist);
	return ;
}

void	draw_rays(t_mlx *mlx)
{
	int		ray_num;
	int		current_ray;

	ray_num = SCREEN_WIDTH;
	current_ray = 0;
	while (current_ray < ray_num)
	{
		calculate_rays(mlx, current_ray);
		render_ray(mlx, current_ray);
		current_ray++;
	}
	return ;
}

void	draw_screen(t_mlx *mlx)
{
	int				screen_y;
	int				screen_x;
	unsigned int	color;

	screen_x = 0;
	while (screen_x < SCREEN_WIDTH)
	{
		screen_y = 0;
		color = mlx->ceiling;
		while (screen_y < (SCREEN_HEIGHT / 2))
		{
			render_sky_floor_assist(mlx, screen_x, screen_y, color);
			screen_y++;
		}
		color = mlx->floor;
		while (screen_y < SCREEN_HEIGHT)
		{
			render_sky_floor_assist(mlx, screen_x, screen_y, color);
			screen_y++;
		}
		screen_x++;
	}
	return ;
}

int	draw_pixels(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	draw_screen(mlx);
	draw_rays(mlx);
	while (i < mlx->map.height)
	{
		j = -1;
		while (++j < mlx->map.width)
		{
			if (mlx->map.matrix[i][j] == 1)
				draw_square(j, i, mlx, 0x46F209);
			else if (mlx->map.matrix[i][j] == 0 || mlx->map.matrix[i][j] == 9
				|| mlx->map.matrix[i][j] == 8 || mlx->map.matrix[i][j] == 5
				|| mlx->map.matrix[i][j] == 7 || mlx->map.matrix[i][j] == 6)
				draw_square(j, i, mlx, 0x1B5108);
		}
		i++;
	}
	draw_rays_minimap(mlx);
	draw_square(mlx->player.player_coords[0],
		mlx->player.player_coords[1], mlx, 0xFFFFFF);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->mlx_img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx			mlx;

	if (!check_args(argc, argv))
		return (1);
	if (!init_mlx_cub(&mlx, argv[1]) || !parse(&mlx, &mlx.map))
		exit_cub(&mlx);
	mlx.player.player_fov = M_PI / 4;
	get_player_spawn(&mlx);
	mlx.player.player_plane[0] = -sin(mlx.player.player_angle[0]);
	mlx.player.player_plane[1] = cos(mlx.player.player_angle[0]);
	mlx.player.raycast.ray_first_angle = mlx.player.player_angle[0]
		- ((M_PI / 3) / 2);
	mlx_hook(mlx.mlx_win, 17, 1L << 0, exit_cub, &mlx);
	mlx_key_hook(mlx.mlx_win, key_handler, &mlx);
	mlx_loop_hook(mlx.mlx, draw_pixels, &mlx);
	mlx_loop(mlx.mlx);
	exit_cub(&mlx);
}
