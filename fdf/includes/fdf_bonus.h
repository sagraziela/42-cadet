/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:24:25 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/06 11:50:27 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <unistd.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "./libft.h"
# include "./get_next_line.h"

# define WIDTH 1910
# define HEIGHT 990
# define MENU_WIDTH 320

# define DOWN0 0x000ed1
# define DOWN1 0x1c29d6
# define DOWN2 0x3944db
# define DOWN3 0x555ee0
# define DOWN4 0x8e94eb
# define DOWN5 0xc6c9f5

# define WHITE 0xffffff77

# define UP1 0xff730077
# define UP2 0xe3830377
# define UP3 0xaaa20a77
# define UP4 0x71c11177
# define UP5 0x1cef1b77

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
	int				pos_x;
	int				pos_y;
}	t_point;

typedef struct s_map
{
	int		height;
	int		width;
	int		**matrix;
	float	angle;
	int		mid_h;
	int		mid_w;
}	t_map;

typedef struct s_cam
{
	float	x_pos;
	float	y_pos;
}	t_cam;

typedef struct s_fdf
{
	char		*name;
	int			argc;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_point		*cords;
	int			color;
	int			z_max;
	int			z_min;
	int			z_scale;
	int			z_highest;
	int			z_pos;
	int			zoom;
	t_map		*map;
}	t_fdf;

void	init_fdf_variables(t_fdf *fdf, char *map_name, int n_args);
t_map	*map_init(t_map *map);
t_point	*cords_init(t_point *cords);
t_map	*read_map(char *file, t_map *map);
void	ft_render(void *param);
void	set_start(t_fdf *fdf, int x1, int y1);
void	set_end(t_fdf *fdf, int x2, int y2);
void	set_z(t_fdf *fdf, t_point *cords, t_map *map);
void	set_cords_scale(t_fdf *fdf);
void	bresenham(t_fdf *fdf);
void	centralize(t_fdf *fdf);
void	zoom(t_fdf *fdf, int *zoom);
void	isometric(t_fdf *fdf, float *x, float *y, int z);
void	set_color(t_fdf *fdf, int x, int y);
void	handle_keyboard(mlx_key_data_t keydata, void *param);
void	handle_mouse(double xdelta, double ydelta, void *param);
void	exit_fdf(t_fdf *fdf);

#endif
