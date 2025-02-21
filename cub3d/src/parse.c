/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:15:37 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/20 13:58:22 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_bool	check_file_format(char *filename, char *format)
{
	int	len;

	len = ft_strlen(filename);
	if (len == 0 || len < 5)
		return (FALSE);
	if (ft_strcmp((filename + len - 4), format) != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		err_msg("Invalid number of arguments.", 0);
		return (FALSE);
	}
	if (!check_file_format(argv[1], ".cub"))
	{
		err_msg("Invalid arguments.", 0);
		return (FALSE);
	}
	return (TRUE);
}

void	map_to_int(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->tab[i])
	{
		j = 0;
		while (map->tab[i][j])
		{
			map_setter(map, i, j);
			j++;
		}
		i++;
	}
	return ;
}

int	check_player(char **map)
{
	int	i;
	int	j;
	int	plr_count;

	i = 0;
	plr_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == NORTH || map[i][j] == SOUTH
				|| map[i][j] == EAST || map[i][j] == WEST)
				plr_count++;
			j++;
		}
		i++;
	}
	if (plr_count != 1)
	{
		err_msg("Invalid number of players.", 0);
		return (0);
	}
	return (1);
}

t_bool	parse(t_mlx *mlx, t_map *map)
{
	if (!check_map_closed(mlx, map))
		return (FALSE);
	if (!check_player(map->tab))
		return (FALSE);
	map_to_int(map);
	return (TRUE);
}
