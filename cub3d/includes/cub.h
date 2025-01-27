#ifndef CUB_H
# define CUB_H

# include "./libft.h"
# include "../minilibx-linux/mlx.h"
# include "ansi_color_codes.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define WND_HEIGHT 500
# define WND_WIDTH 850

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}		t_bool;

typedef struct s_data
{
    char    **map;
    char    *map_file;
    int     map_length;
    void    *mlx;
    void    *wnd;
    void    *img;
    int     wnd_height;
    int     wnd_width;
}       t_data;

t_bool	parse(t_data *data);
void	clear(t_data *data);

#endif
