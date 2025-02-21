/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:18:46 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/18 15:28:15 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ns_border(t_mlx *mlx, char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == ZERO || map[i][j] == NORTH
			|| map[i][j] == SOUTH || map[i][j] == EAST
			|| map[i][j] == WEST)
			return (-1);
		else if (map[i][j] == SPACE && check_space_out(mlx, map, i, j))
			return (-1);
		j++;
	}
	return (0);
}

int	check_ew_border(char **map, int i)
{
	int	j;
	int	width;

	j = -1;
	width = ft_strlen(map[i]);
	while (++j < width)
	{
		if (map[i][j] == ZERO || map[i][j] == NORTH || map[i][j] == SOUTH ||
			map[i][j] == EAST || map[i][j] == WEST)
		{
			if (j == 0 || j == width - 1)
				return (-1);
			if (!check_line_limit(map, i, j) || !check_line_mid(map, i, j))
				return (-1);
		}
	}
	return (0);
}

t_bool	check_map_closed(t_mlx *mlx, t_map *map)
{
	int	i;
	int	res;

	i = 0;
	while (i < map->height)
	{
		res = 0;
		if (i == 0 || i == map->height - 1)
			res = check_ns_border(mlx, map->tab, i);
		else
			res = check_ew_border(map->tab, i);
		if (res == -1)
		{
			err_msg("Map is not closed", 1);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
