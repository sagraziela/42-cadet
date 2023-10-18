/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:31:16 by gde-souz          #+#    #+#             */
/*   Updated: 2023/10/18 13:02:44 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

// int	handle_key(int key, void *data)
// {
// 	printf("%d", key);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_struct	*fdf;
	int			i;
	int			j;
	int			map_area;

	i = 0;
	j = 0;
	if (argc == 2)
	{
		fdf = (t_struct *)malloc(sizeof(t_struct));
		if (!fdf)
			return (0);
		map_area = read_map(argv[1], fdf);
		while (i < fdf->height)
		{
			while (j < fdf->width)
			{
				printf("%3d", fdf->matrix[i][j]);
				j++;
			}
			printf("\n");
			j = 0;
			i++;
		}
	}
	return (0);
}

// cc *.c ./gnl/*.c
// ./a.out ./test_maps/42.fdf
