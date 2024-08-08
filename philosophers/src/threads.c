/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:49:00 by root              #+#    #+#             */
/*   Updated: 2024/08/06 18:51:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    lock_forks(t_dinner **dinner, int left, int right, int id)
{
    size_t  time;

    pthread_mutex_lock((*dinner)->table_forks[left]);
    time = get_current_time();
    printf("%ld %d has taken a fork.\n", time, id);
    pthread_mutex_lock((*dinner)->table_forks[right]);
    time = get_current_time();
    printf("%ld %d has taken a fork.\n", time, id);
}

void    unlock_forks(t_dinner **dinner, int left, int right)
{
    pthread_mutex_unlock((*dinner)->table_forks[left]);
    pthread_mutex_unlock((*dinner)->table_forks[right]);
}

void    handle_thread(t_philo **philo)
{
    t_dinner    **dinner;
    size_t      time;

    dinner = &((*philo)->dinner);
    lock_forks(dinner, (*philo)->left_fork, (*philo)->right_fork, (*philo)->id);
    time = get_current_time();
    if (!(*philo)->last_meal)
        (*philo)->init_time = time;
    if (time > (*philo)->time_to_die)
    {
        printf("PHILO %d IS DEAD 💀\n", (*philo)->id);
        return ;
    }
    printf("%ld %d is eating 🍽\n", time, (*philo)->id);
    usleep(to_micro((*dinner)->time_to_eat));
    unlock_forks(dinner, (*philo)->left_fork, (*philo)->right_fork);
    time = get_current_time();
    (*philo)->last_meal = time;
    (*philo)->time_to_die = time + (*dinner)->time_to_die;       //NEEDS TO BE DINAMIC
    printf("%ld %d is sleeping 💤\n", time, (*philo)->id);
    usleep(to_micro((*dinner)->time_to_sleep));
    time = get_current_time();
    printf("%ld %d is thinking 🤔\n", time, (*philo)->id);
}
