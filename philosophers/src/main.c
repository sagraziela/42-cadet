/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/08/16 18:32:03 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*dine(void *arg)
{
	t_philo		*philo;
	t_dinner	**dinner;
	int			n;

	philo = (t_philo *)arg;
	dinner = &philo->dinner;
	n = 0;
	while ((!philo->dinner->infinite_dinner
			&& n < philo->dinner->total_meals && !must_stop(dinner))
		|| (philo->dinner->infinite_dinner && !must_stop(dinner)))
	{
		if (!must_stop(dinner))
			handle_eat(dinner, &philo);
		if (!must_stop(dinner))
			handle_sleep(dinner, &philo);
		n++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dinner	*dinner;
	t_philo		**philos;
	int			i;

	i = 0;
	dinner = init_dinner(argc, argv);
	if (dinner)
	{
		philos = init_philo(&dinner, dinner->philos_num);
		while (i < dinner->philos_num)
		{
			pthread_create(&philos[i]->thread, NULL, dine, (void *)philos[i]);
			i++;
		}
		i = 0;
		while (i < dinner->philos_num)
		{
			pthread_join(philos[i]->thread, NULL);
			i++;
		}
		clear(philos);
		return (0);
	}
	print_error();
	return (1);
}
