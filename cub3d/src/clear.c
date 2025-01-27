#include "../includes/cub.h"

void	clear(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_length)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	mlx_destroy_image(data->mlx, data->img);
	mlx_clear_window(data->mlx, data->wnd);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
	free(data);
}
