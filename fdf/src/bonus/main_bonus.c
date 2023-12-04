/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:51:51 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/04 11:22:29 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

t_fdf	*fdf_init(int n_args, char *map_name)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	init_fdf_variables(fdf, map_name, n_args);
	fdf->map = map_init(fdf->map);
	if (!fdf->map)
		free(fdf);
	fdf->cords = cords_init(fdf->cords);
	if (!fdf->cords)
	{
		free(fdf->map);
		free(fdf->cords);
	}
	if (fdf->name == NULL)
		fdf->name = "error";
	return (fdf);
}

int	check_file_format(const char *filename)
{
	char	*format;

	format = ft_strnstr(filename, ".fdf", ft_strlen(filename));
	if (!format)
		return (0);
	return (1);
}

void	error_message(void)
{
	ft_putstr_fd("---------- This is gde-souz's FDF! ----------\n\n", 1);
	ft_putstr_fd("HOW TO RUN:\n", 1);
	ft_putstr_fd("'./fdf  [map file]'		|		", 1);
	ft_putstr_fd("ATENTION: the file must end with '.fdf'\n\n", 1);
	ft_putstr_fd("EXAMPLE: ./fdf ./test_maps/42.fdf\n", 1);
	ft_putstr_fd("---------- ----------------------- ----------\n", 1);
}

void	exit_fdf(void *param)
{
	t_fdf	*fdf;
	int		i;

	fdf = (t_fdf *)param;
	if (fdf->map->matrix)
	{
		i = 0;
		while (fdf->map->matrix[i])
		{
			free(fdf->map->matrix[i]);
			fdf->map->matrix[i] = NULL;
			++i;
		}
		free(fdf->map->matrix);
		free(fdf->name);
		mlx_terminate(fdf->mlx);
	}
	free(fdf->map);
	free(fdf->cords);
	free(fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = fdf_init(argc, argv[1]);
	if (argv[1])
	{
		fdf->mlx = mlx_init(WIDTH, HEIGHT, fdf->name, true);
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		if (check_file_format(fdf->name) && fdf->mlx && fdf->img)
		{
			fdf->map = read_map(argv[1], fdf->map);
			mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
			ft_render(fdf);
			mlx_scroll_hook(fdf->mlx, handle_mouse, fdf);
			mlx_key_hook(fdf->mlx, handle_keyboard, fdf);
			mlx_loop(fdf->mlx);
			exit_fdf(fdf);
			return (EXIT_SUCCESS);
		}
		mlx_terminate(fdf->mlx);
	}
	error_message();
	exit_fdf(fdf);
	return (EXIT_FAILURE);
}
