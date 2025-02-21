/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:21:00 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/18 15:27:06 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		err_msg("Failed to open the map.\n", 0);
	return (fd);
}

int	check_textures_colors(t_mlx *mlx, char *line, int i)
{
	int	res;

	res = 0;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		res = handle_texture(mlx, &mlx->n_wall_texture, line, i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		res = handle_texture(mlx, &mlx->s_wall_texture, line, i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		res = handle_texture(mlx, &mlx->w_wall_texture, line, i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		res = handle_texture(mlx, &mlx->e_wall_texture, line, i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		res = handle_colors(&mlx->floor, line);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		res = handle_colors(&mlx->ceiling, line);
	return (res);
}

int	handle_line(t_mlx *mlx, char *line)
{
	int		i;
	int		res;

	if (!line[0])
		return (0);
	res = 0;
	i = ft_spaceskip(line, 0);
	res = check_textures_colors(mlx, line, i);
	if (res != 0)
		return (res);
	else
	{
		i = 0;
		if (!mlx->n_wall_texture.width || !mlx->s_wall_texture.width
			|| !mlx->e_wall_texture.width || !mlx->w_wall_texture.width
			|| !mlx->floor || !mlx->ceiling)
			return (err_msg("Map is not valid", 0));
		else if (line[i] == WALL || line[i] == SPACE)
		{
			mlx->map.tab[mlx->map.height] = ft_strdup(line);
			mlx->map.height++;
		}
	}
	return (res);
}

t_bool	read_map(int fd, t_mlx *mlx)
{
	char	*line;
	char	*sub_line;
	int		line_wid;
	int		res;

	if (fd < 0)
		return (FALSE);
	mlx->map.tab = (char **)ft_calloc(10000, sizeof(char *));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		sub_line = ft_strtrim(line, "\n");
		line_wid = ft_strlen(sub_line);
		if (line_wid > mlx->map.width)
			mlx->map.width = line_wid;
		res = handle_line(mlx, sub_line);
		free(line);
		free(sub_line);
		if (res == -1)
			return (FALSE);
	}
	return (TRUE);
}
