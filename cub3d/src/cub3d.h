/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:28:35 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/20 13:39:08 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "../libft/libft.h"

# define M_HEIGHT 20
# define M_WIDTH 48
# define PLAYER_RADIUS 0.5
# define SQUARE_SIZE 8
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define ROTATION_SPEED 0.05
# define MOVEMENT_SPEED 0.2

# define ZERO '0'
# define WALL '1'
# define SPACE ' '
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'
# define HEXA_CHARS "0123456789ABCDEF"

enum e_texture
{
	NO,
	SO,
	EA,
	WE,
	F,
	C,
	DO,
	TOT,
};

typedef struct s_bresenham
{
	double			start_x;
	double			start_y;
	double			end_x;
	double			end_y;
	double			distance_x;
	double			distance_y;
	double			s_x;
	double			s_y;
	double			err;
	double			err2;
	int				map_x;
	int				map_y;
}					t_bresenham;

typedef struct s_raycast
{
	double			ray_first_angle;
	double			ray_fakedist;
	double			ray_truedist;
	double			ray_coords[2];
	double			ray_dir_vector[2];
	double			ray_angle;
	double			ray_spacing;
	double			ray_x;
	double			ray_y;
	double			dist_to_closest_x;
	double			dist_to_closest_y;
	double			dist_to_next_x;
	double			dist_to_next_y;
	double			step_x;
	double			step_y;
	double			wall_x;
	double			texture_step;
	int				map_x;
	int				map_y;
	int				first_wall_pixel;
	int				last_wall_pixel;
	int				current_wall_pixel;
	int				line_height;
	unsigned int	ray_color;
	t_bresenham		bresenham;
}					t_raycast;

typedef struct s_player
{
	double			player_coords[2];
	double			player_angle[2];
	double			player_vector[2];
	double			player_plane[2];
	double			player_camera_x;
	double			player_fov;
	double			new_x;
	double			new_y;
	double			old_dir_x;
	double			old_plane_x;
	t_raycast		raycast;
}					t_player;

typedef struct s_map
{
	char	**tab;
	int		**matrix;
	char	*file;
	int		height;
	int		width;
}	t_map;

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}		t_bool;

typedef enum s_coords
{
	x,
	y
}					t_coords;

typedef struct s_texture
{
	void	*mlx;
	void	*img;
	void	*win;
	char	*addr;
	int		texture_x;
	int		texture_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	double	texture_position;
}				t_texture;

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	void			*mlx_img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				side;
	int				height;
	t_map			map;
	t_player		player;
	t_texture		n_wall_texture;
	t_texture		w_wall_texture;
	t_texture		s_wall_texture;
	t_texture		e_wall_texture;
	unsigned int	floor;
	unsigned int	ceiling;
}					t_mlx;

/* INT, FLOAT, DOUBLE, UNSIGNED*/
unsigned int	get_pixel_img(t_texture *img, int x, int y);
int				check_cub(char *filename);
int				draw_pixels(t_mlx *mlx);
int				key_handler(int keysym, t_mlx *mlx);
int				kill_mlx(t_mlx	*mlx);

/* VOID */
void			kill_program(char *errmsg, int errnum);
void			bresenham_algorithm_minimap(t_mlx *mlx, int ray_color);
void			bresenham_pixel_draw(t_mlx *mlx,
					t_bresenham *b, int ray_color);
void			bresenham_variable_init(t_mlx *mlx, t_bresenham *b);
void			calculate_rays(t_mlx *mlx, int current_ray);
void			calculate_rays_var_init1(t_mlx *mlx, int current_ray);
void			calculate_rays_var_init2(t_mlx *mlx);
void			calculate_rays_var_init3(t_mlx *mlx);
void			calculate_rays_var_init4(t_mlx *mlx);
void			draw_rays(t_mlx *mlx);
void			draw_rays_minimap(t_mlx *mlx);
void			draw_screen(t_mlx *mlx);
void			draw_square(double start_x, double start_y,
					t_mlx *mlx, unsigned int color);
void			east_player_spawn(t_mlx *mlx, int i, int j);
void			get_player_spawn(t_mlx *mlx);
void			kill_program(char *errmsg, int errnum);
void			north_player_spawn(t_mlx *mlx, int i, int j);
bool			player_collision_detector_backward(t_mlx *mlx);
bool			player_collision_detector_forward(t_mlx *mlx);
bool			player_collision_detector_left(t_mlx *mlx);
bool			player_collision_detector_right(t_mlx *mlx);
void			player_move_backward(t_mlx *mlx);
void			player_move_forward(t_mlx *mlx);
void			player_move_left(t_mlx *mlx);
void			player_move_right(t_mlx *mlx);
void			player_turn_left(t_mlx *mlx);
void			player_turn_right(t_mlx *mlx);
void			put_pixel_img(t_mlx *mlx, int x, int y, unsigned int color);
void			render_ray(t_mlx *mlx, int current_ray);
void			render_ray_assist2(t_mlx *mlx, t_texture *img);
void			render_sky_floor_assist(t_mlx *mlx, int screen_x,
					int screen_y, unsigned int color);
void			south_player_spawn(t_mlx *mlx, int i, int j);
void			west_player_spawn(t_mlx *mlx, int i, int j);

//	STRUCTS
t_texture		new_file_img(char *path, t_mlx *mlx);
t_texture		render_ray_assist1(t_mlx *mlx);

/* PARSING BRANCH */
t_bool			read_map(int fd, t_mlx *mlx);
unsigned int	check_rgb(char *str);
unsigned int	rgb_to_dec(int *rgb);
t_bool			parse(t_mlx *mlx, t_map *map);
t_bool			init_mlx_cub(t_mlx	*mlx, char *filename);
t_bool			check_args(int argc, char **argv);
t_bool			check_file_format(char *filename, char *format);
void			map_setter(t_map *map, int i, int j);
int				open_file(char *filename);
int				handle_texture(t_mlx *mlx, t_texture *tex, char *line, int i);
int				ft_spaceskip(char *line, int i);
int				handle_line(t_mlx *mlx, char *line);
t_bool			check_map_closed(t_mlx *mlx, t_map *map);
void			free_matrix(void **matrix);
unsigned int	handle_colors(unsigned int *obj_ref, char *line);
unsigned int	parse_colors(unsigned int *obj_ref,
					char **split);
t_bool			validate_digits(char *nbr);
int				err_msg(char *errmsg, int errnum);
t_bool			check_obj(char c, int obj);
t_bool			check_line_limit(char **map, int i, int j);
t_bool			check_line_mid(char **map, int i, int j);
int				check_space_out(t_mlx *mlx, char **map, int i, int j);
int				exit_cub(t_mlx *mlx);
void			clear(t_mlx *mlx);

#endif