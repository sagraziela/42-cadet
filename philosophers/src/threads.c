/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:49:00 by root              #+#    #+#             */
/*   Updated: 2024/08/16 18:37:39 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	if (left_fork)
		pthread_mutex_unlock(left_fork);
	if (right_fork)
		pthread_mutex_unlock(right_fork);
	return ;
}

static void	handle_single_philo(t_dinner **dinner, t_philo **philo)
{
	pthread_mutex_lock(&(*dinner)->table_forks[(*philo)->left_fork]);
	print_action(philo, dinner, L_FORK);
	unlock_forks(&(*dinner)->table_forks[(*philo)->left_fork], NULL);
	usleep((*dinner)->time_to_die);
	check_if_alive(philo);
	return ;
}

t_bool	lock_forks(t_dinner **dinner, t_philo **philo)
{
	if (!must_stop(dinner) || !check_if_alive(philo))
	{
		pthread_mutex_lock(&(*dinner)->table_forks[(*philo)->left_fork]);
		print_action(philo, dinner, L_FORK);
		if (must_stop(dinner))
			return (FALSE);
	}
	if (!must_stop(dinner) || !check_if_alive(philo))
	{
		pthread_mutex_lock(&(*dinner)->table_forks[(*philo)->right_fork]);
		print_action(philo, dinner, R_FORK);
		if (must_stop(dinner))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

void	handle_sleep(t_dinner **dinner, t_philo **philo)
{
	size_t	time;

	time = get_current_time();
	(*philo)->time_of_death = time + (*dinner)->time_to_die;
	if (((*dinner)->time_to_sleep + time) < (*philo)->time_of_death
		&& !must_stop(dinner))
	{
		print_action(philo, dinner, SLEEP);
		usleep((*dinner)->time_to_sleep);
		if (!must_stop(dinner))
			print_action(philo, dinner, THINK);
	}
	else if (!must_stop(dinner))
	{
		print_action(philo, dinner, SLEEP);
		usleep(((*philo)->time_of_death - time));
		to_stop(dinner);
		print_action(philo, dinner, DIE);
	}
	return ;
}

void	handle_eat(t_dinner **dinner, t_philo **philo)
{
	if ((*dinner)->philos_num == 1)
	{
		handle_single_philo(dinner, philo);
		return ;
	}
	start_getting_forks(dinner, philo);
	if ((*dinner)->philos_num > 1 && lock_forks(dinner, philo))
	{
		end_getting_forks(dinner);
		print_action(philo, dinner, EAT);
		usleep((*dinner)->time_to_eat);
		(*dinner)->meals_had++;
	}
	end_getting_forks(dinner);
	unlock_forks(&(*dinner)->table_forks[(*philo)->left_fork], &(*dinner)->table_forks[(*philo)->right_fork]);
	return ;
}
