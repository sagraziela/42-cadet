/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:35:01 by gde-souz          #+#    #+#             */
/*   Updated: 2023/10/18 18:09:22 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./MLX42/include/MLX42/MLX42.h"

#define WIDTH 630
#define HEIGHT 630

static mlx_image_t	*g_image;

int	main(int argc, char **argv)
{
	mlx_t	mlx;

	argc = 2;
	argv[0] = "**";
	mlx = mlx_init(WIDTH, HEIGHT, "MLX-TEST", true);
	g_image = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_image, 1, 1);
	mlx_loop_hook(mlx, function, mlx);
}
// cc ./draw.c ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm  