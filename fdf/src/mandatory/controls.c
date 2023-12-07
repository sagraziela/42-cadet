/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:16:35 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/07 14:02:37 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

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

void	handle_z_scale(t_fdf *fdf, int n)
{
	mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
	fdf->z_scale += n;
	ft_render(fdf);
}

void	handle_keyboard(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(fdf->mlx);
		return ;
	}
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W))
		rotate_img(fdf, 'y', 0.1);
	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S))
		rotate_img(fdf, 'y', -0.1);
	if ((keydata.key == MLX_KEY_KP_ADD || keydata.key == MLX_KEY_EQUAL)
		&& fdf->z_scale < fdf->z_max)
		handle_z_scale(fdf, 1);
	if ((keydata.key == MLX_KEY_KP_SUBTRACT || keydata.key == MLX_KEY_MINUS)
		&& fdf->z_scale > fdf->z_min)
		handle_z_scale(fdf, -1);
}

void	handle_mouse(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (xdelta == 0 && ydelta > 0)
		zoom_img(fdf, 1);
	else if (xdelta == 0 && ydelta < 0)
		zoom_img(fdf, -1);
}
