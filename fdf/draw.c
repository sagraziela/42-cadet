/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:35:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/01 14:18:12 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

t_fdf	*fdf_init(int n_args, char *map_name)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->name = map_name;
	fdf->argc = n_args;
	fdf->zoom = 20;
	fdf->color = 0;
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
	fdf->cords->steps = 0;
	if (fdf->name == NULL)
		fdf->name = "error";
	return (fdf);
}

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void	check_z(t_fdf *fdf, int i, int j, char axis)
{
	if (axis == 'x')
	{
		while (fdf->cords->x1 <= fdf->cords->x2)
		{
			if ((fdf->map->matrix[i][j] > 0) ||
				(i > 0 && fdf->map->matrix[i - 1][j] > 0))
				fdf->color = 0xF842E4;
			else
				fdf->color = 0xffffff77;
			mlx_put_pixel(fdf->img, fdf->cords->x1++, fdf->cords->y1, fdf->color);
		}
	}
	else if (axis == 'y')
	{
		while (fdf->cords->y1 <= fdf->cords->y2)
		{
			if ((fdf->map->matrix[i][j] > 0) ||
				(j > 0 && fdf->map->matrix[i][j - 1] > 0))
				fdf->color = 0xF842E4;
			else
				fdf->color = 0xffffff77;
			mlx_put_pixel(fdf->img, fdf->cords->x1, fdf->cords->y1++, fdf->color);
		}
	}
}

void	draw_lines(t_fdf *fdf, int x_len, int y_len)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < fdf->cords->steps - 1)
	{
		while (i < fdf->map->height - 1 && j < fdf->map->width - 1)
		{
			fdf->cords->x2 = fdf->cords->x1 + x_len;
			fdf->cords->y2 = fdf->cords->y1 + y_len;
			check_z(fdf, i, j, 'y');
			fdf->cords->y1 -= (int)y_len + 1;
			check_z(fdf, i, j, 'x');
			j++;
		}
		j = 0;
		fdf->cords->y1 = fdf->zoom + (y_len * i);
		fdf->cords->x1 = fdf->zoom;
	}
	while (fdf->cords->x1 <= fdf->cords->x2)
		mlx_put_pixel(fdf->img, fdf->cords->x1++, fdf->cords->y2, fdf->color);
	fdf->cords->y1 = fdf->zoom;
	while (fdf->cords->y1 <= fdf->cords->y2)
		mlx_put_pixel(fdf->img, fdf->cords->x2, fdf->cords->y1++, fdf->color);
}

void	bresenham(t_fdf *fdf)
{
	float	x_len;
	float	y_len;

	fdf->cords->x1 = fdf->zoom;
	fdf->cords->y1 = fdf->zoom;
	fdf->cords->x2 = fdf->cords->x1 + fdf->map->width;
	fdf->cords->y2 = fdf->cords->y1 + fdf->map->height;
	x_len = fdf->cords->x2 - fdf->cords->x1;
	y_len = fdf->cords->y2 - fdf->cords->y1;
	if (x_len > y_len)
		fdf->cords->steps = x_len;
	else
		fdf->cords->steps = y_len;
	x_len = 800 / (int)x_len;
	y_len = 480 / (int)y_len;
	draw_lines(fdf, x_len, y_len);
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
			mlx_put_pixel(fdf->img, i, j, 0x0000077);
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
