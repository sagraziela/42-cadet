/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/08/22 18:28:14 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_bool	must_eat(t_dinner **dinner, t_philo **philo)
{
	t_bool	all_full;

	all_full = TRUE;
	if ((*dinner)->infinite_dinner && !must_stop(dinner))
		return (TRUE);
	pthread_mutex_lock((*dinner)->eat_mutex);
	if ((*dinner)->philos_full == (*dinner)->philos_num)
		all_full = TRUE;
	pthread_mutex_unlock((*dinner)->eat_mutex);
	if (((*philo)->meals_had < (*dinner)->total_meals
	|| !all_full) && !must_stop(dinner))
	{
		return (TRUE);
	}
	return (FALSE);
}

static void	*dine(void *arg)
{
	t_philo		*philo;
	t_dinner	**dinner;

	philo = (t_philo *)arg;
	dinner = &philo->dinner;
	if (philo->id == 2)
		usleep(10);
	while (must_eat(dinner, &philo))
	{
		if (!must_stop(dinner))
			handle_eat(dinner, &philo);
		philo->meals_had++;
		if (!must_stop(dinner))
			handle_sleep(dinner, &philo);
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
