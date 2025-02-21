/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:17:40 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/18 15:41:31 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	err_msg(char *errmsg, int errnum)
{
	if (errmsg != 0 || errnum != 2)
		ft_putendl_fd("Error\n", 2);
	if (errmsg != 0)
		ft_putstr_fd(errmsg, 2);
	if (errmsg != 0 && errnum != 0)
		ft_putstr_fd(": ", 2);
	if (errnum != 0)
		ft_putstr_fd(strerror(errnum), 2);
	if (errmsg != 0 || errnum != 0)
		ft_putendl_fd("", 2);
	return (-1);
}

void	free_matrix(void **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	clear_texture_imgs(t_mlx *mlx)
{
	if (mlx->n_wall_texture.img)
		mlx_destroy_image(mlx->mlx, mlx->n_wall_texture.img);
	if (mlx->s_wall_texture.img)
		mlx_destroy_image(mlx->mlx, mlx->s_wall_texture.img);
	if (mlx->e_wall_texture.img)
		mlx_destroy_image(mlx->mlx, mlx->e_wall_texture.img);
	if (mlx->w_wall_texture.img)
		mlx_destroy_image(mlx->mlx, mlx->w_wall_texture.img);
}

void	clear(t_mlx *mlx)
{
	if (!mlx->mlx)
		return ;
	if (mlx->map.tab)
		free_matrix((void **)mlx->map.tab);
	if (mlx->map.matrix)
		free_matrix((void **)mlx->map.matrix);
	clear_texture_imgs(mlx);
	if (mlx->mlx_img)
	{
		mlx_destroy_image(mlx->mlx, mlx->mlx_img);
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	}
	mlx_destroy_display(mlx->mlx);
	mlx_loop_end(mlx->mlx);
	free(mlx->mlx);
}

int	exit_cub(t_mlx *mlx)
{
	clear(mlx);
	exit(0);
	return (0);
}
