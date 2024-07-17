/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/07/17 10:49:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    clear(t_dinner **dinner, int philos_num)
{
    int i;

    i = 0;
    while (i < philos_num)
    {
        free((*dinner)->philos[i].forks);
        i++;
    }
}

size_t    get_current_time(void)
{
    struct  timeval tval;
    time_t  t;
    struct  tm *info;
    t_time  *time;
    size_t  total;
    
    gettimeofday(&tval, NULL);
    t = tval.tv_sec;
    info = localtime(&t);
    time = malloc(sizeof(t_time));
    time->hour = info->tm_hour * 60 * 60 * 1000;
    time->min = info->tm_min * 60 * 1000;
    time->sec = info->tm_sec * 1000;
    total = time->hour + time->min + time->sec;
    return (total);
}

void    *dine(void *arg)
{
    t_philo *philo;
    size_t  time;
    int     i;

    philo = (t_philo*)arg;
    i = 0;
    while (i < 3)
    {
        if (philo->must_stop == FALSE)
        {
            pthread_mutex_lock(*(philo->forks->left_fork));
            pthread_mutex_lock(*(philo->forks->right_fork));
            printf("Philo %d EAT - %ld - %ld\n", philo->id, philo->time_to_eat, get_current_time());
            if (!philo->last_meal)
                philo->init_time = get_current_time();
            usleep(philo->time_to_eat);
            philo->last_meal = get_current_time();
            philo->must_stop = TRUE;
            pthread_mutex_unlock(*(philo->forks->left_fork));
            pthread_mutex_unlock(*(philo->forks->right_fork));
       }
        time = get_current_time();
        printf("Philo %d SLEEP - %ld - %ld\n", philo->id, philo->time_to_sleep, time);
        usleep(philo->time_to_sleep);
        time = get_current_time();
        printf("Philo %d THINK - %d - %ld\n", philo->id, 1000000, time);
        philo->must_stop = FALSE;
        i++;
    }
    return (NULL);
}

int main(void)
{
    t_dinner    *dinner;
    int         philos_num;
    int         i;

    i = 0;
    philos_num = 2;
    dinner = malloc(sizeof(t_dinner));
    init_dinner(&dinner, philos_num);
    while (i < philos_num)
    {
        dinner->philos[i] = init_philo(&dinner->table_forks, i, philos_num);
        if (pthread_create(&dinner->philos[i].thread, NULL, dine, (void*)&dinner->philos[i]) != 0)
            return (1);
        i++;
    }
   i = 0;
    while (i < philos_num)
    {
        if (pthread_join(dinner->philos[i].thread, NULL) != 0)
            return (2);
       i++;
    }
    clear(&dinner, philos_num);
    exit(0);
}
