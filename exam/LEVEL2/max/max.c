/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:38:46 by gde-souz          #+#    #+#             */
/*   Updated: 2024/01/12 16:59:05 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	max(int *tab, unsigned int len)
{
	unsigned int	i;
	int				largest;

	if (!tab)
		return (0);
	i = 0;
	largest = tab[i];
	while (i < len)
	{
		if (tab[i] > largest)
			largest = tab[i];
	}
	return (largest);
}
