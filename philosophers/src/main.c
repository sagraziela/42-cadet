/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/08/23 15:13:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	add_philos_full(t_dinner **dinner)
{
	pthread_mutex_lock((*dinner)->eat_mutex);
	(*dinner)->philos_full++;
	pthread_mutex_unlock((*dinner)->eat_mutex);
}

static t_bool	check_philos_full(t_dinner **dinner)
{
	t_bool	eat;

	pthread_mutex_lock((*dinner)->eat_mutex);
	if ((*dinner)->philos_full == (*dinner)->philos_num)
		eat = FALSE;
	else
		eat = TRUE;
	pthread_mutex_unlock((*dinner)->eat_mutex);
	return (eat);
}

static t_bool	must_eat(t_dinner **dinner, t_philo **philo)
{
	t_bool	stop;
	t_bool	eat;

	eat = TRUE;
	stop = must_stop(dinner);
	if ((*dinner)->infinite_dinner && !stop)
		return (TRUE);
	eat = check_philos_full(dinner);
	if (!(*dinner)->infinite_dinner && !stop
		&& ((*philo)->meals_had < (*dinner)->total_meals || eat))
		return (TRUE);
	return (FALSE);
}

static void	*dine(void *arg)
{
	t_philo		*philo;
	t_dinner	**dinner;

	philo = (t_philo *)arg;
	dinner = &philo->dinner;
	if ((*dinner)->philos_num < 50
		&& (((*dinner)->philos_num % 2 == 0 && philo->id == 3)
			|| ((*dinner)->philos_num % 2 == 1 && philo->id == 2)))
		usleep(10);
	while (must_eat(dinner, &philo))
	{
		if (!must_stop(dinner))
		{
			handle_eat(dinner, &philo);
			philo->meals_had++;
			if (philo->meals_had == (*dinner)->total_meals)
				add_philos_full(dinner);
		}
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
