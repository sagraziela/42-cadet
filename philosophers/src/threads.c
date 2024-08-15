/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:49:00 by root              #+#    #+#             */
/*   Updated: 2024/08/15 16:25:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool    lock_forks(t_dinner **dinner, t_philo **philo)
{
    pthread_mutex_lock(&(*dinner)->table_forks[(*philo)->left_fork]);
    print_action(philo, dinner, L_FORK);
    if (must_stop(dinner))
    {
        pthread_mutex_unlock(&(*dinner)->table_forks[(*philo)->left_fork]);
        return (FALSE);
    }
    if ((*dinner)->philos_num == 1)
    {
        usleep((*dinner)->time_to_die);
        check_if_alive(philo);
        return (FALSE);
    }
    pthread_mutex_lock(&(*dinner)->table_forks[(*philo)->right_fork]);
    print_action(philo, dinner, R_FORK);
    if (must_stop(dinner) || check_if_alive(philo))
    {
        unlock_forks(dinner, (*philo)->left_fork, (*philo)->right_fork);
        return (FALSE);
    }
    return (TRUE);
}

void    unlock_forks(t_dinner **dinner, int left, int right)
{
    pthread_mutex_unlock(&(*dinner)->table_forks[left]);
    pthread_mutex_unlock(&(*dinner)->table_forks[right]);
    return ;
}

void    handle_sleep(t_dinner **dinner, t_philo **philo)
{
    size_t  time;
 
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
        usleep(((*philo)->time_of_death - time));
        to_stop(dinner);
        print_action(philo, dinner, DIE);
    }
    return ;
}

void    handle_eat(t_dinner **dinner, t_philo **philo)
{
    if (lock_forks(dinner, philo))
    {
        print_action(philo, dinner, EAT);
        usleep((*dinner)->time_to_eat);
        unlock_forks(dinner, (*philo)->left_fork, (*philo)->right_fork);
        (*dinner)->meals_had++;
    }
    return ;
}
