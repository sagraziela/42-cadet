/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiguel- <lmiguel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:18:51 by lmiguel-          #+#    #+#             */
/*   Updated: 2025/02/18 15:31:27 by lmiguel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	handle_xpm(t_mlx *mlx, t_texture *tex, char *file)
{
	int	fd;

	if (!check_file_format(file, ".xpm"))
		return (err_msg("Wrong file format for texture", 0));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err_msg("Failed to open texture file", 0));
	close(fd);
	tex->img = mlx_xpm_file_to_image(mlx->mlx, file, &tex->width, &tex->height);
	if (tex->img == NULL)
		return (err_msg("Failed to convert .xpm to image", 0));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (1);
}

int	ft_spaceskip(char *line, int i)
{
	while (line[i] == SPACE)
		i++;
	return (i);
}

int	handle_texture(t_mlx *mlx, t_texture *tex, char *line, int i)
{
	char	*file;
	int		res;

	i = ft_spaceskip(line, i + 2);
	file = ft_strdup(line + i);
	if (!file)
		return (-1);
	res = handle_xpm(mlx, tex, file);
	free(file);
	return (res);
}
