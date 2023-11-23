/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:16:35 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/23 16:06:08 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

void	rotate_img(t_fdf *fdf, char axis, float n)
{
	mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	if (axis == 'x')
		fdf->map->angle += n;
	else if (axis == 'y')
		fdf->map->angle += n;
	ft_render(fdf);
}

void	zoom_img(t_fdf *fdf, int n)
{
	mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	fdf->zoom += n;
	ft_render(fdf);
}

// void	change_z_lenght(); // CONSTRUIR

void	handle_keyboard(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	printf("angle = %f	|	", fdf->map->angle);
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		&& (fdf->map->angle < fdf->map->max_angle))
		rotate_img(fdf, 'y', 0.1);
	else if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		&& (fdf->map->angle > fdf->map->min_angle))
		rotate_img(fdf, 'y', -0.1);
	// else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
	// 	reset_img(fdf, 'x', -10);
	// else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
	// 	reset_img(fdf, 'x', 10);
	// else if ((keydata.key == MLX_KEY_KP_ADD && fdf->z < fdf->z_max))
	// 	change_z_lenght(fdf);
	// else if ((keydata.key == MLX_KEY_MINUS && fdf->z > fdf->z_min))
	// 	change_z_lenght(fdf);
	// else if (keydata.key == MLX_KEY_ESCAPE)
	// 	mlx_close_window(fdf->mlx);
}

void	handle_mouse(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	//printf("x_delta: %f	| y_delta: %f\n", xdelta, ydelta);
	if (xdelta == 0 && ydelta > 0)
		zoom_img(fdf, 1);
	else if (xdelta == 0 && ydelta < 0)
		zoom_img(fdf, -1);
}
