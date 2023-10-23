/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:35:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/10/23 17:14:51 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./MLX42/include/MLX42/MLX42.h"

#define WIDTH 1320
#define HEIGHT 860

static mlx_image_t	*g_image;

void	bresenham(float x1, float y1, float x2, float y2)
{
	float	x_len;
	float	y_len;
	float	steps;

	x_len = x2 - x1;
	y_len = y2 - y1;
	if (x_len > y_len)
		steps = x_len;
	else
		steps = y_len;
	x_len /= steps;
	y_len /= steps;
	while (x1 <= x2 && y1 <= y2)
	{
		mlx_put_pixel(g_image, x1, y1, 0xffffff);
		x1 += x_len;
		y1 += y_len;
	}
}

void	fill_matrix(int *matrix)
{
	int	i;

	i = 0;
	printf("Linha 50\n");
	matrix = (int *)malloc(sizeof(int) * 5);
	matrix[4] = '\0';
	while (matrix[i] != '\0')
	{
		matrix[i] = 1;
		i++;
	}
}

void	ft_render(void *param)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	matrix[7][7] = {{1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}};

	param = 0;
	x = 0;
	y = 0;
	while (y < (int)g_image->height)
	{
		while (x < (int)g_image->width)
		{
			mlx_put_pixel(g_image, x, y, 353935);
			x++;
		}
		x = 0;
		y++;
	}
	i = 0;
	j = 0;
	x = 50;
	y = 50;
	while (matrix[i + 1][j])
	{
		while (matrix[i][j + 1] != '\0')
		{
			bresenham(x, y, x, y + 100);
			bresenham(x, y, x + 100, y);
			j++;
			x += 100;
			printf("passou aqui [%d][%d]\n", i, j);
		}
		bresenham(x, y, x, y + 100);
		j = 0;
		i++;
		y += 100;
		if (!matrix[i + 1][j])
		{
			bresenham(50, y, x, y);
		}
		x = 50;
	}
}

// void	ft_keyboard(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		g_image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		g_image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		g_image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		g_image->instances[0].x += 5;
// }

int	main(int argc, char **argv)
{
	mlx_t	*mlx;

	argc = 2;
	argv[0] = "**";
	mlx = mlx_init(WIDTH, HEIGHT, "MLX-TEST", true);
	g_image = mlx_new_image(mlx, WIDTH, HEIGHT);
	printf("width: %d || height: %d\n", g_image->width, g_image->height);
	mlx_image_to_window(mlx, g_image, 0, 0);
	mlx_loop_hook(mlx, ft_render, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
// cc ./draw.c ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm  