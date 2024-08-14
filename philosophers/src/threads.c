/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:49:00 by root              #+#    #+#             */
/*   Updated: 2024/08/14 15:50:06 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    lock_forks(t_dinner **dinner, t_philo **philo)
{
    if (!must_stop(dinner, philo))
    {
        pthread_mutex_lock(&(*dinner)->table_forks[(*philo)->left_fork]);
        if (!check_if_alive(philo) || must_stop(dinner, philo))
            return ;
        print_action(philo, dinner, L_FORK);
        if ((*dinner)->philos_num == 1)
        {
            usleep((*dinner)->time_to_die);
            check_if_alive(philo);
            return ;
        }
        pthread_mutex_lock(&(*dinner)->table_forks[(*philo)->right_fork]);
        if (!check_if_alive(philo) || must_stop(dinner, philo))
            return ;
        print_action(philo, dinner, R_FORK);
    }
}

void    unlock_forks(t_dinner **dinner, int left, int right)
{
    pthread_mutex_unlock(&(*dinner)->table_forks[left]);
    pthread_mutex_unlock(&(*dinner)->table_forks[right]);
    return ;
}

t_bool    handle_forks_dinamic(t_dinner **dinner, t_philo **philo)
{
    if (((*dinner)->meals_had == 0 && (*philo)->id % 2 == 1)
        || ((*philo)->id <= (*dinner)->philos_num / 2)
        || (*dinner)->philos_num == 2)
    {
        pthread_mutex_lock((*dinner)->eat_mutex);
    }
    lock_forks(dinner, philo);
    pthread_mutex_unlock((*dinner)->eat_mutex);
    if (must_stop(dinner, philo))
    {
        unlock_forks(dinner, (*philo)->left_fork, (*philo)->right_fork);
        return (FALSE);
    }
    return (TRUE);
}

void    handle_sleep(t_dinner **dinner, t_philo **philo)
{
    size_t  time;
 
    time = get_current_time();
    if (((*dinner)->time_to_sleep + time) < (*philo)->time_of_death
        && !must_stop(dinner, philo))
    {
        print_action(philo, dinner, SLEEP);
        usleep((*dinner)->time_to_sleep);
        if (check_if_alive(philo) && !must_stop(dinner, philo))
            print_action(philo, dinner, THINK);
    }
    else if (!must_stop(dinner, philo))
    {
        usleep(((*philo)->time_of_death - time));
        to_stop(dinner);
        print_action(philo, dinner, DIE);
    }
    return ;
}

void    handle_eat(t_dinner **dinner, t_philo **philo)
{
    size_t  time;

    if (!must_stop(dinner, philo) && handle_forks_dinamic(dinner, philo))
    {
        print_action(philo, dinner, EAT);
        usleep((*dinner)->time_to_eat);
        unlock_forks(dinner, (*philo)->left_fork, (*philo)->right_fork);
        (*dinner)->meals_had++;
        time = get_current_time();
        (*philo)->time_of_death = time + (*dinner)->time_to_die;
    }
    return ;
}
