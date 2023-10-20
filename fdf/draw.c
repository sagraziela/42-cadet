/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:35:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/10/20 18:28:46 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./MLX42/include/MLX42/MLX42.h"

#define WIDTH 1320
#define HEIGHT 860

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

static mlx_image_t	*g_image;

//breseham is not working yet
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
	while (x_len <= x2 || y_len <= y2)
	{
		mlx_put_pixel(g_image, x1, y1, 0xffffff);
		x1 += x_len;
		y1 += y_len;
	}
}

void	ft_render(void *param)
{
	int	x;
	int	y;
	int	color;

	param = 0;
	x = 0;
	y = 0;
	color = 353935;
	while (y < (int)g_image->height)
	{
		while (x < (int)g_image->width)
		{
			mlx_put_pixel(g_image, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_pixel(g_image, 10, 10, 0xffffff);
	mlx_put_pixel(g_image, 11, 10, 0xffffff);
	mlx_put_pixel(g_image, 12, 10, 0xffffff);
	mlx_put_pixel(g_image, 13, 10, 0xffffff);
	mlx_put_pixel(g_image, 14, 10, 0xffffff);
	mlx_put_pixel(g_image, 15, 10, 0xffffff);
	mlx_put_pixel(g_image, 16, 10, 0xffffff);
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
	mlx_image_to_window(mlx, g_image, 0, 0);
	mlx_loop_hook(mlx, ft_render, mlx);
	//mlx_loop_hook(mlx, ft_keyboard, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
// cc ./draw.c ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm  