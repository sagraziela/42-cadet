/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:09:32 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/18 15:46:08 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	init_texture(t_texture *texture)
{
	texture->mlx = NULL;
	texture->img = NULL;
	texture->addr = NULL;
	texture->win = NULL;
	texture->texture_x = 0;
	texture->texture_y = 0;
	texture->bits_per_pixel = 0;
	texture->line_length = 0;
	texture->endian = 0;
	texture->width = 0;
	texture->height = 0;
	texture->texture_position = 0;
}

t_bool	init_matrix(t_mlx *mlx)
{
	int	i;

	mlx->map.matrix = (int **)ft_calloc(mlx->map.height + 1, sizeof(int *));
	if (!mlx->map.matrix)
		return (FALSE);
	i = 0;
	while (i < mlx->map.height)
	{
		mlx->map.matrix[i] = (int *)ft_calloc(mlx->map.width + 1, sizeof(int));
		if (!mlx->map.matrix[i])
		{
			while (mlx->map.matrix[--i])
				free(mlx->map.matrix[i]);
			return (FALSE);
		}
		i++;
	}
	mlx->map.matrix[i] = NULL;
	return (TRUE);
}

t_bool	init_map(t_mlx *mlx, char *filename, int fd)
{
	mlx->map.file = filename;
	mlx->map.tab = NULL;
	mlx->map.matrix = NULL;
	mlx->map.height = 0;
	mlx->map.width = 0;
	if (!read_map(fd, mlx) || !init_matrix(mlx))
		return (FALSE);
	return (TRUE);
}

t_bool	init_mlx_cub(t_mlx	*mlx, char *filename)
{
	int		fd;
	t_bool	res;

	mlx->mlx = NULL;
	fd = open_file(filename);
	if (fd < 0)
		return (FALSE);
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "cub3d");
	mlx->mlx_img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->mlx_img,
			&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	init_texture(&mlx->n_wall_texture);
	init_texture(&mlx->s_wall_texture);
	init_texture(&mlx->e_wall_texture);
	init_texture(&mlx->w_wall_texture);
	mlx->floor = 0;
	mlx->ceiling = 0;
	res = init_map(mlx, filename, fd);
	close(fd);
	if (!res)
		return (FALSE);
	return (TRUE);
}
