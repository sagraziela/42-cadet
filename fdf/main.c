/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:51:51 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/23 15:24:03 by gde-souz         ###   ########.fr       */
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
	fdf->zoom = 5;
	fdf->color = 0;
	fdf->map = malloc(sizeof(t_map));
	if (!fdf->map)
		return (NULL);
	fdf->map->angle = 0.8;
	fdf->map->min_angle = 0.0;
	fdf->map->max_angle = 1.2;
	fdf->cords = malloc(sizeof(t_point));
	if (!fdf->cords)
		return (NULL);
	fdf->cords->x1 = 0;
	fdf->cords->y1 = 0;
	fdf->cords->x2 = 0;
	fdf->cords->y2 = 0;
	fdf->cords->steps = 0;
	fdf->cords->pos_x = 0;
	fdf->cords->pos_y = 0;
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

void	exit_fdf(void *param, char *filename)
{
	t_fdf	*fdf;
	int		i;

	fdf = (t_fdf *)param;
	i = 0;
	mlx_terminate(fdf->mlx);
	free(filename);
	free(fdf->cords);
	while (fdf->map->matrix[i])
	{
		free(fdf->map->matrix[i]);
		fdf->map->matrix[i] = NULL;
		++i;
	}
	free(fdf->map->matrix);
	free(fdf->map);
	free(fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	char	*filename;

	if (!check_file_format(argv[1]))
		return (EXIT_FAILURE);
	fdf = fdf_init(argc, argv[1]);
	if (argc != 2 || !fdf)
		return (EXIT_FAILURE);
	filename = ft_strjoin("FDF - ", ft_strrchr(argv[1], '/'));
	fdf->mlx = mlx_init(WIDTH, HEIGHT, filename, true);
	if (fdf->mlx)
	{
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		fdf->map = read_map(argv[1], fdf->map);
		printf("img_w: %d || img_h: %d\n", fdf->img->width, fdf->img->height);
		mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
		ft_render(fdf);
		mlx_scroll_hook(fdf->mlx, handle_mouse, fdf);
		mlx_key_hook(fdf->mlx, handle_keyboard, fdf);
		mlx_loop(fdf->mlx);
		exit_fdf(fdf, filename);
	}
	return (EXIT_SUCCESS);
}
//cc ./*.c ./gnl/*.c ./libft/*.c ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
