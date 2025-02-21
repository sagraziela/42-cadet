/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:49:08 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/18 15:50:17 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_setter(t_map *map, int i, int j)
{
	if (map->tab[i][j] == ZERO)
		map->matrix[i][j] = 0;
	else if (map->tab[i][j] == WALL)
		map->matrix[i][j] = 1;
	else if (map->tab[i][j] == SPACE)
		map->matrix[i][j] = 5;
	else if (map->tab[i][j] == EAST)
		map->matrix[i][j] = 6;
	else if (map->tab[i][j] == NORTH)
		map->matrix[i][j] = 7;
	else if (map->tab[i][j] == WEST)
		map->matrix[i][j] = 8;
	else if (map->tab[i][j] == SOUTH)
		map->matrix[i][j] = 9;
	else
		map->matrix[i][j] = -1;
}
