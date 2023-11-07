/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:35:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/07 18:10:02 by gde-souz         ###   ########.fr       */
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
	fdf->zoom = 30;
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

void	draw_line(t_fdf *fdf)
{
	int	i;

	i = 0;
	fdf->color = 0xffffff77;
	while (fdf->cords->x1 <= fdf->cords->x2 && fdf->cords->y1 <= fdf->cords->y2)
	{
		mlx_put_pixel(fdf->img, fdf->cords->x1, fdf->cords->y1, fdf->color);
		fdf->cords->x1 += fdf->cords->x_len;
		fdf->cords->y1 += fdf->cords->y_len;
	}
}

void	zoom(t_point *cords, int zoom)
{
	cords->x1 *= zoom;
	cords->y1 *= zoom;
	cords->x2 *= zoom;
	cords->y2 *= zoom;
}

void	bresenham(t_fdf *fdf)
{
	fdf->cords->x_len = fdf->cords->x2 - fdf->cords->x1;
	fdf->cords->y_len = fdf->cords->y2 - fdf->cords->y1;
	if (fdf->cords->x_len > fdf->cords->y_len)
		fdf->cords->steps = fdf->cords->x_len;
	else
		fdf->cords->steps = fdf->cords->y_len;
	fdf->cords->x_len = fdf->cords->x_len / fdf->cords->steps;
	fdf->cords->y_len = fdf->cords->y_len / fdf->cords->steps;
}

void	set_start(t_fdf *fdf, int x1, int y1)
{
	fdf->cords->x1 = x1;
	fdf->cords->y1 = y1;
}
void	set_end(t_fdf *fdf, int x2, int y2)
{
	fdf->cords->x2 = x2;
	fdf->cords->y2 = y2;
}

void	ft_render(void *param)
{
	int		x;
	int		y;
	t_fdf	*fdf;

	y = 0;
	fdf = (t_fdf *)param;
	while (y < fdf->map->height - 1)
	{
		x = 0;
		while (x < fdf->map->width - 1)
		{
			set_start(fdf, x, y);
			set_end(fdf, x + 1, y);
			bresenham(fdf);
			zoom(fdf->cords, fdf->zoom);
			draw_line(fdf);
			// -------------------------
			set_start(fdf, x, y);
			set_end(fdf, x, y + 1);
			bresenham(fdf);
			zoom(fdf->cords, fdf->zoom);
			draw_line(fdf);
			x++;
		}
		y++;
	}
	set_start(fdf, 0, fdf->cords->y2);
	set_end(fdf, fdf->cords->x2 + fdf->zoom, fdf->cords->y2);
	printf("x1 = %f || y1 = %f || x2 = %f || y2 = %f\n\n", fdf->cords->x1, fdf->cords->y1, fdf->cords->x2, fdf->cords->y2);
	bresenham(fdf);
	draw_line(fdf);
	set_start(fdf, fdf->cords->x2, 0);
	set_end(fdf, fdf->cords->x2, fdf->cords->y2);
	bresenham(fdf);
	draw_line(fdf);
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
//cc ./*.c ./gnl/*.c ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
