/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors_assist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:33:47 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/19 13:00:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	rgb_to_dec(int *rgb)
{
	unsigned int	new;

	new = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (new);
}

t_bool	validate_digits(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

unsigned int	parse_colors(unsigned int *obj_ref,
				char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		*obj_ref = check_rgb(split[i]);
		if ((int)obj_ref[i] == -1)
			return (-1);
		i++;
	}
	return (1);
}
