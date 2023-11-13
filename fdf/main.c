/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:51:51 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/13 16:11:42 by gde-souz         ###   ########.fr       */
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
	fdf->zoom = 12;
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
