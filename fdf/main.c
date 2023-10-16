/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:31:16 by gde-souz          #+#    #+#             */
/*   Updated: 2023/10/16 14:20:47 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	handle_key(int key, void *data)
{
	printf("%d", key);
	return (0);
}

int	main(int argc, char **argv)
{
	t_struct	*fdf;

	fdf = (*fdf)malloc(sizeof(fdf));
	if (!fdf)
		return (NULL);
	return (0);
}
