/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:24:02 by gde-souz          #+#    #+#             */
/*   Updated: 2023/11/13 16:10:57 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "./get_next_line.h"

# define WIDTH 1980
# define HEIGHT 980

typedef struct s_point
{
	float			x1;
	float			x2;
	float			y1;
	float			y2;
	int				z1;
	int				z2;
	float			x_len;
	float			y_len;
	unsigned int	steps;
}	t_point;

typedef struct s_map
{
	int		height;
	int		width;
	int		**matrix;
	int		z_max;
	int		z_min;
}	t_map;

typedef struct s_fdf
{
	char		*name;
	int			argc;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_point		*cords;
	int			color;
	float		z;
	float		zoom;
	t_map		*map;
}	t_fdf;

char	**ft_split(char const *s, char c);
t_map	*read_map(char *file, t_map *map);
void	ft_render(void *param);
void	set_start(t_fdf *fdf, int x1, int y1);
void	set_end(t_fdf *fdf, int x2, int y2);
void	bresenham(t_fdf *fdf);
void	centralize(t_fdf *fdf);
void	zoom(t_point *cords, int zoom);
void	set_color(t_fdf *fdf, int x, int y);
void	isometric(float *x, float *y, int z);

#endif
