/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:26:40 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/23 15:15:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	**init_philo(t_dinner **dinner, int num)
{
	t_philo	**philo;
	int		i;

	philo = (t_philo **)malloc(sizeof(t_philo *) * (num + 1));
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		philo[i]->id = i + 1;
		philo[i]->time_of_death = (*dinner)->init_time + (*dinner)->time_to_die;
		philo[i]->last_meal = 0;
		philo[i]->meals_had = 0;
		philo[i]->dinner = *dinner;
		philo[i]->left_fork = i;
		if (i + 1 == num)
			philo[i]->right_fork = 0;
		else
			philo[i]->right_fork = philo[i]->id;
	}
	philo[num] = NULL;
	return (philo);
}

static void	init_mutexes(t_dinner **dinner)
{
	int	i;

	pthread_mutex_init((*dinner)->stop_mutex, NULL);
	pthread_mutex_init((*dinner)->print_mutex, NULL);
	pthread_mutex_init((*dinner)->eat_mutex, NULL);
	i = -1;
	while (++i < (*dinner)->philos_num)
		pthread_mutex_init(&(*dinner)->table_forks[i], NULL);
}

t_dinner	*init_dinner(int argc, char **argv)
{
	t_dinner	*dinner;

	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		return (NULL);
	if (!handle_args(argc, argv, &dinner) || dinner->philos_num == 0)
	{
		free(dinner);
		return (NULL);
	}
	dinner->init_time = get_current_time();
	dinner->stop = FALSE;
	dinner->first_death = TRUE;
	dinner->philos_full = 0;
	dinner->stop_mutex = malloc(sizeof(pthread_mutex_t));
	dinner->print_mutex = malloc(sizeof(pthread_mutex_t));
	dinner->eat_mutex = malloc(sizeof(pthread_mutex_t));
	dinner->table_forks = malloc(dinner->philos_num * sizeof(pthread_mutex_t));
	init_mutexes(&dinner);
	return (dinner);
}
