/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:49:00 by root              #+#    #+#             */
/*   Updated: 2024/08/12 14:57:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool  shall_halt(t_dinner **dinner, t_philo **philo)
{
    t_bool temp;
    
    (void)philo;
    pthread_mutex_lock((*dinner)->halt_mutex);
    temp = (*dinner)->halt;
    pthread_mutex_unlock((*dinner)->halt_mutex);
    return (temp);
}

void    to_halt(t_dinner **dinner, t_philo **philo)
{
    (void)philo;
    pthread_mutex_lock((*dinner)->halt_mutex);
    (*dinner)->halt = TRUE;
    pthread_mutex_unlock((*dinner)->halt_mutex);
    return ;
}

t_bool  check_if_alive(t_philo **philo)
{
    size_t time;
    
    time = get_current_time();
    if (time >= (*philo)->time_of_death && !shall_halt(&(*philo)->dinner, philo))
    {
        to_halt(&(*philo)->dinner, philo);
        printf("%ld %d IS DeEaAaD 💀\n", get_dinner_time(&(*philo)->dinner, time), (*philo)->id);
        return (FALSE);
    }
    return (TRUE);
}

void    lock_forks(t_dinner **dinner, t_philo **philo)
{
    size_t  time;

    if (!shall_halt(dinner, philo))
    {
        pthread_mutex_lock((*dinner)->table_forks[(*philo)->left_fork]);
        if (!check_if_alive(philo) || shall_halt(dinner, philo))
            return ;
        time = get_current_time();
        printf("%ld %d has taken L fork.\n", get_dinner_time(dinner, time), (*philo)->id);
        pthread_mutex_lock((*dinner)->table_forks[(*philo)->right_fork]);
        if (!check_if_alive(philo) || shall_halt(dinner, philo))
            return ;
        time = get_current_time();
        printf("%ld %d has taken R fork.\n", get_dinner_time(dinner, time), (*philo)->id);
    }
}

void    unlock_forks(t_dinner **dinner, int left, int right)
{
    if ((*dinner)->table_forks[left])
        pthread_mutex_unlock((*dinner)->table_forks[left]);
    if ((*dinner)->table_forks[right])
        pthread_mutex_unlock((*dinner)->table_forks[right]);
    return ;
}

void    handle_sleep(t_dinner **dinner, t_philo **philo)
{
    size_t  time;
 
    time = get_current_time();
    if (((*dinner)->time_to_sleep + time) < (*philo)->time_of_death
        && !shall_halt(dinner, philo))
    {
        printf("%ld %d is sleeping 💤\n", get_dinner_time(dinner, time), (*philo)->id);
        usleep((*dinner)->time_to_sleep);
        if (check_if_alive(philo) && !shall_halt(dinner, philo))
        {
            time = get_current_time();
            printf("%ld %d is thinking 🤔\n", get_dinner_time(dinner, time), (*philo)->id);
        }
    }
    else if (!shall_halt(dinner, philo))
    {
        usleep(((*philo)->time_of_death - time));
        to_halt(dinner, philo);
        printf("PHILO %d IS DEAD 💀\n", (*philo)->id);
    }
    return ;
}

void    handle_eat(t_dinner **dinner, t_philo **philo)
{
    size_t  time;

    if (!shall_halt(dinner, philo))
    {
        lock_forks(dinner, philo);
        if (shall_halt(dinner, philo))
        {
            unlock_forks(dinner, (*philo)->left_fork, (*philo)->right_fork);
            return ;
        }
        time = get_current_time();
        printf("%ld %d is eating 🍽\n", get_dinner_time(dinner, time), (*philo)->id);
        usleep((*dinner)->time_to_eat);
    }
    unlock_forks(dinner, (*philo)->left_fork, (*philo)->right_fork);
}

void    handle_thread(t_philo **philo)
{
    t_dinner    **dinner;
    size_t      time;

    dinner = &((*philo)->dinner);
    if (!shall_halt(dinner, philo))
    {
        handle_eat(dinner, philo);
        time = get_current_time();
        (*philo)->last_meal = time;
        (*philo)->time_of_death = time + (*dinner)->time_to_die;
        if (!shall_halt(dinner, philo))
            handle_sleep(dinner, philo);
    }
    return ;
}
