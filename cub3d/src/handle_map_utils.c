/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:18:35 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/18 15:27:20 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	check_obj(char c, int obj)
{
	if (obj == 1 && c != WALL)
	{
		return (FALSE);
	}
	if (c != ZERO && c != NORTH && c != SOUTH
		&& c != EAST && c != WEST && c != WALL)
	{
		return (FALSE);
	}
	return (TRUE);
}

t_bool	check_line_limit(char **map, int i, int j)
{
	if (j == 1 && (!check_obj(map[i][0], 1)
		|| !check_obj(map[i][2], 0) || !check_obj(map[i + 1][1], 0)
		|| !check_obj(map[i - 1][1], 0)))
	{
		return (FALSE);
	}
	else if (j == (int)ft_strlen(map[i]) - 2 && (!check_obj(map[i][j - 1], 0)
		|| !check_obj(map[i][j + 1], 1) || !check_obj(map[i - 1][j], 0)
		|| !check_obj(map[i + 1][j], 0)))
	{
		return (FALSE);
	}
	return (TRUE);
}

t_bool	check_line_mid(char **map, int i, int j)
{
	if (j <= 1 || j >= (int)ft_strlen(map[i]) - 2)
		return (TRUE);
	else if (!check_obj(map[i][j - 1], 0) || !check_obj(map[i][j + 1], 0) ||
		!check_obj(map[i - 1][j], 0) || !check_obj(map[i + 1][j], 0))
		return (FALSE);
	return (TRUE);
}

int	check_space_out(t_mlx *mlx, char **map, int i, int j)
{
	if (i == 0)
	{
		while (map[i][j] == SPACE && i < mlx->map.height - 1)
		{
			if (map[i + 1][j] == WALL)
				break ;
			i++;
		}
		if (i == mlx->map.height - 1)
			return (1);
	}
	else if (i == mlx->map.height - 1)
	{
		while (map[i][j] == SPACE && i > 0)
		{
			if (map[i][j] == WALL && map[i + 1][j] == SPACE && i > 0)
				break ;
			i--;
		}
		if (i == 0)
			return (1);
	}
	return (0);
}
