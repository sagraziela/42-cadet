/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:51:51 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/06 16:24:48 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	check_file_format(const char *filename)
{
	int		fd;
	char	*format;

	format = ft_strnstr(filename, ".fdf", ft_strlen(filename));
	if (!format)
	{
		ft_putstr_fd("\nFILE FORMAT NOT SUPPORTED.\n\n", 1);
		return (1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 1)
	{
		ft_putstr_fd("\nFILE NOT FOUND.\n\n", 1);
		return (1);
	}
	close(fd);
	return (0);
}

t_fdf	*fdf_init(int n_args, char *map_name)
{
	t_fdf	*fdf;

	if (map_name != NULL && !check_file_format(map_name))
	{
		fdf = malloc(sizeof(t_fdf));
		if (!fdf)
			return (NULL);
		init_fdf_variables(fdf, map_name, n_args);
	}
	else
		return (NULL);
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

void	error_message(void)
{
	ft_putstr_fd("---------- This is gde-souz's FDF! ----------\n\n", 1);
	ft_putstr_fd("HOW TO RUN:\n", 1);
	ft_putstr_fd("'./fdf  [map file]'		|		", 1);
	ft_putstr_fd("ATTENTION: the file must end with '.fdf'\n\n", 1);
	ft_putstr_fd("EXAMPLE: ./fdf ./test_maps/42.fdf\n\n", 1);
	ft_putstr_fd("---------- ----------------------- ----------\n", 1);
}

void	exit_fdf(t_fdf *fdf)
{
	int		i;

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
		mlx_close_window(fdf->mlx);
		mlx_terminate(fdf->mlx);
	}
	free(fdf->name);
	free(fdf->map);
	free(fdf->cords);
	free(fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = fdf_init(argc, argv[1]);
	if (fdf)
	{
		fdf->map = read_map(argv[1], fdf->map);
		if (fdf->map)
		{
			fdf->mlx = mlx_init(WIDTH, HEIGHT, fdf->name, 0);
			fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
			mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
			ft_render(fdf);
			mlx_scroll_hook(fdf->mlx, handle_mouse, fdf);
			mlx_key_hook(fdf->mlx, handle_keyboard, fdf);
			mlx_loop(fdf->mlx);
			exit_fdf(fdf);
			return (EXIT_SUCCESS);
		}
	}
	error_message();
	return (EXIT_FAILURE);
}
