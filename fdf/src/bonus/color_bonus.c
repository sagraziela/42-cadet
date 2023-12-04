/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:19:56 by gde-souz          #+#    #+#             */
/*   Updated: 2023/12/04 18:44:22 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf_bonus.h"

static int	check_pos_or_neg(t_fdf *fdf, int x, int y)
{
	if (fdf->map->matrix[y][x] > 0 ||
		(y > 0 && fdf->map->matrix[y - 1][x] > 0 && fdf->cords->y_len == 0) ||
		(x > 0 && fdf->map->matrix[y][x - 1] > 0 && fdf->cords->x_len == 0) ||
		(y == 0 && fdf->map->matrix[y + 1][x] > 0
			&& fdf->cords->x_len < fdf->cords->y_len) ||
		(x == 0 && fdf->map->matrix[y][x + 1] > 0
			&& fdf->cords->x_len > fdf->cords->y_len))
	{
		return (1);
	}
	else if (fdf->map->matrix[y][x] < 0 ||
		(y > 0 && fdf->map->matrix[y - 1][x] < 0 && fdf->cords->y_len == 0) ||
		(x > 0 && fdf->map->matrix[y][x - 1] < 0 && fdf->cords->x_len == 0) ||
		(y == 0 && fdf->map->matrix[y + 1][x] < 0
			&& fdf->cords->x_len < fdf->cords->y_len) ||
		(x == 0 && fdf->map->matrix[y][x + 1] < 0
			&& fdf->cords->x_len > fdf->cords->y_len))
	{
		return (-1);
	}
	else
		return (0);
}

void	set_color(t_fdf *fdf, int x, int y)
{
	if (check_pos_or_neg(fdf, x, y) == 1)
	{
		fdf->color = UP5;
	}
	else if (check_pos_or_neg(fdf, x, y) == -1)
		fdf->color = UP1;
	else
		fdf->color = WHITE;
}
