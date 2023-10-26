/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:35:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/10/26 18:39:30 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

t_fdf	*fdf_init(int n_args, char *map_name)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->map = malloc(sizeof(t_map));
	if (!fdf->map)
		return (NULL);
	fdf->cords = malloc(sizeof(t_point));
	if (!fdf->cords)
		return (NULL);
	fdf->cords->x1 = 0;
	fdf->cords->y1 = 0;
	fdf->cords->x2 = 0;
	fdf->cords->y2 = 0;
	fdf->name = map_name;
	if (fdf->name == NULL)
		fdf->name = "error";
	fdf->argc = n_args;
	return (fdf);
}

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void	bresenham(t_fdf *fdf)
{
	float	x_len;
	float	y_len;
	float	steps;

	fdf->cords->x1 = 50;
	fdf->cords->y1 = 50;
	x_len = fdf->cords->x2 - fdf->cords->x1;
	y_len = fdf->cords->y2 - fdf->cords->y1;
	fdf->cords->x2 = fdf->cords->x1 + x_len;
	fdf->cords->y2 = fdf->cords->y1 + y_len;
	if (x_len > y_len)
		steps = x_len;
	else
		steps = y_len;
	x_len /= steps;
	y_len /= steps;
	printf("map_w: %i || map_h: %i\n", fdf->map->width, fdf->map->height);
	// ADD VERIFICAÇÃO DO TAMANHO DO MAPA
	while (fdf->cords->x1 <= fdf->cords->x2 - 1)
	{
		while (fdf->cords->y1 <= fdf->cords->y2)
		{
			mlx_put_pixel(fdf->img, fdf->cords->x1, fdf->cords->y1, 0xffffff77);
			fdf->cords->y1 += y_len;
		}
		mlx_put_pixel(fdf->img, fdf->cords->x1, fdf->cords->y1, 0xffffff77);
		fdf->cords->x1 += x_len;
	}
}

void	ft_render(void *param)
{
	int		i;
	int		j;
	t_fdf	*fdf;

	i = 0;
	j = 0;
	fdf = (t_fdf *)param;
	while (i < WIDTH)
	{
		while (j < HEIGHT)
		{
			mlx_put_pixel(fdf->img, i, j, 353935);
			j++;
		}
		j = 0;
		i++;
	}
	bresenham((t_fdf *)param);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = fdf_init(argc, argv[1]);
	if (argc != 2 || !fdf)
		return (EXIT_FAILURE);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "MLX - ... ", true);
	if (fdf->mlx)
	{
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		fdf->map = read_map(argv[1], fdf->map);
		printf("img_w: %d || img_h: %d\n", fdf->img->width, fdf->img->height);
		mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
		mlx_loop_hook(fdf->mlx, ft_render, fdf);
		mlx_loop(fdf->mlx);
	}
	else if (!fdf->mlx)
		return (EXIT_FAILURE);
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}
// cc ./draw.c ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
//cc ./*.c ./gnl/*.c ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

	// printf("map_w: %i || map_h: %i\n", fdf->map->width, fdf->map->height);
	// while (i < fdf->map->height)
	// {
	// 	while (j < fdf->map->width)
	// 	{
	// 		//printf("matrix[%d][%d]: %d\n", i, j, fdf->map->matrix[i][j]);
	// 		bresenham(fdf, fdf->x, fdf->y + 100);
	// 		bresenham(fdf, fdf->x + 100, fdf->y);
	// 		j++;
	// 		fdf->x += 100;
	// 	}
	// 	bresenham(fdf, fdf->x, fdf->y + 100);
	// 	j = 0;
	// 	i++;
	// 	fdf->y += 100;
	// 	if (!fdf->map->matrix[i + 1][j])
	// 	{
	// 		//bresenham(50, y, x, y);
	// 	}
	// 	fdf->x += (fdf->x * i);
	// }