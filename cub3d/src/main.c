#include "../includes/cub.h"

int file_format_is_valid(char *file)
{
    int len;
    char *type;

    len = ft_strlen(file);
    type = ft_substr(file, len - 4, 4);
    if (ft_strncmp(type, ".cub", 4))
    {
        free(type);
        return (FALSE);
    }
    free(type);
    return (TRUE);
}

int check_user_input(int argc, char **argv)
{
    if (argc != 2 || (argc == 2 && !file_format_is_valid(argv[1])))
    {
        printf("ERROR: the program needs an argument to be executed, which shall be a map file in the '.cub' format. \
        \nUSAGE: \
        ./cub map.cub\n\n");
        return (FALSE);
    }
    return (TRUE);
}

int open_map(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        printf("ERROR: failed to open file '%s'.\n", filename);
    return (fd);
}

char    **read_map(int fd, t_data *data)
{
    char    *line;
    char    *sub_line;
    char    **map;

    if (fd < 0)
        return (NULL);
    map = ft_calloc(10000, sizeof(char *));
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        sub_line = ft_substr(line, 0, ft_strlen(line) - 1);
        map[data->map_length] = sub_line;
        printf("%s\n", map[data->map_length]);
        data->map_length++;
        free(line);
    }
    return (map);
}

void    data_init(t_data *data, char *filename)
{
    data->map_file = filename;
    data->map_length = 0;
    data->map = read_map(open_map(filename), data);
    data->mlx = NULL;
    data->wnd = NULL;
    data->img = NULL;
	data->wnd_height = WND_HEIGHT;
	data->wnd_width = WND_WIDTH;
}

// static void	set_frame_image_pixel(t_data *data, void *image, int x, int y)
// {
// 	if (data->texture_pixels[y][x] > 0)
// 		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
// 	else if (y < data->wnd_height / 2)
// 		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
// 	else if (y < data->wnd_height -1)
// 		set_image_pixel(image, x, y, data->texinfo.hex_floor);
// }

static void	render(t_data *data)
{
	int		x;
	int		y;

	//init_img(data, &data->img, data->wnd_width, data->wnd_height);
    data->img = mlx_new_image(data->mlx, WND_WIDTH, WND_HEIGHT);
	y = 0;
	while (y < data->wnd_height)
	{
		x = 0;
		while (x < data->wnd_width)
		{
            mlx_pixel_put(data->mlx, data->wnd, x, y, 0x00ff00);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->wnd, data->img, WND_WIDTH, WND_HEIGHT);
	mlx_destroy_image(data->mlx, data->img);
}
t_bool    init_cub_mlx(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
	{
        clear(data);
        return (FALSE);
    }
	data->wnd = mlx_new_window(data->mlx, WND_WIDTH, WND_HEIGHT, "CUB-3D");
	if (!data->wnd)
	{
        clear(data);
        return (FALSE);
    }
    return (TRUE);
}

int	main(int argc, char **argv)
{
    t_data  data;

	if (!check_user_input(argc, argv))
        return (1);
    data_init(&data, argv[1]);
    if (!data.map || (data.map && !parse(&data)))
    {
        clear(&data);
        return (1);
    }
    printf("MAP IS VALID\n");
    if (!init_cub_mlx(&data))
        return (1);
    //init_img(data, &data->img, data->wnd_width, data->wnd_height);
    render(&data);
    //mlx_loop_hook(data->mlx, render, data);
    mlx_loop(data.mlx);
    // MAKE EVERYTHING WORK
    clear(&data);
    return (0);
}
