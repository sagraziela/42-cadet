/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:18:25 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/20 13:25:43 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static int	check_comma_pos(char *color_str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (color_str[i])
	{
		if (color_str[i] == ',')
		{
			if (i == 0 || i == (int)ft_strlen(color_str) - 1)
				return (0);
			counter++;
		}
		i++;
	}
	if (counter != 2)
		return (0);
	return (1);
}

int	*check_rgb_assist(char **color)
{
	int	i;
	int	*color_int;

	i = 0;
	color_int = (int *)ft_calloc(4, sizeof(int));
	if (!color_int)
		return (NULL);
	while (color[i])
	{
		if (!validate_digits(color[i]))
		{
			free(color_int);
			return (NULL);
		}
		color_int[i] = ft_atoi(color[i]);
		if (color_int[i] < 0 || color_int[i] > 255)
		{
			free(color_int);
			return (NULL);
		}
		i++;
	}
	return (color_int);
}

unsigned int	check_rgb(char *str)
{
	char			**color;
	int				*color_int;
	unsigned int	color_hexa;

	color = ft_split(str, ',');
	if (!color)
		return (-1);
	color_int = check_rgb_assist(color);
	if (!color_int)
	{
		free_matrix((void **)color);
		free(color_int);
		return (err_msg("Incorrect RGB pattern.", 0));
	}
	color_hexa = rgb_to_dec(color_int);
	free_matrix((void **)color);
	free(color_int);
	return (color_hexa);
}

unsigned int	handle_colors(unsigned int *obj_ref, char *line)
{
	int				i;
	int				len;
	unsigned int	ret;
	char			**split;

	i = ft_spaceskip(line, 1);
	split = ft_split(line + i, ' ');
	if (!split)
		return (err_msg("Failed to allocate memory", 2));
	i = 0;
	while (split[i])
	{
		len = ft_strlen(split[i]);
		if (len < 5 || len > 11 || !check_comma_pos(split[i]))
		{
			free_matrix((void **)split);
			return (err_msg("Incorrect color formatting", 0));
		}
		i++;
	}
	ret = parse_colors(obj_ref, split);
	free_matrix((void **)split);
	return (ret);
}
