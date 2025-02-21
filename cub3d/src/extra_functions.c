/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:20:05 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/17 12:43:38 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_img(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	if (color == 0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < SCREEN_WIDTH
		&& y < SCREEN_HEIGHT)
	{
		dst = mlx->addr + (y * mlx->line_length + x
				* (mlx->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

t_texture	new_file_img(char *path, t_mlx *mlx)
{
	t_texture	image;

	image.win = mlx->mlx_win;
	image.img = mlx_xpm_file_to_image(mlx->mlx, path,
			&image.width, &image.height);
	if (!image.img)
		write(2, "File could not be read\n", 23);
	else
		image.addr = mlx_get_data_addr(image.img, &(image.bits_per_pixel),
				&(image.line_length), &(image.endian));
	return (image);
}

int	kill_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(1);
}

int	check_cub(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len == 0)
		return (0);
	if (len < 5)
		return (0);
	if (ft_strcmp((filename + len - 4), ".cub") != 0)
		return (0);
	return (1);
}

void	get_player_spawn(t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < mlx->map.height)
	{
		x = 0;
		while (x < mlx->map.width)
		{
			if (mlx->map.matrix[y][x] == 6)
				east_player_spawn(mlx, y, x);
			else if (mlx->map.matrix[y][x] == 7)
				north_player_spawn(mlx, y, x);
			else if (mlx->map.matrix[y][x] == 8)
				west_player_spawn(mlx, y, x);
			else if (mlx->map.matrix[y][x] == 9)
				south_player_spawn(mlx, y, x);
			x++;
		}
		y++;
	}
	return ;
}
