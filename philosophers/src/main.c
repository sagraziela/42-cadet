/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/07/17 15:25:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    clear(t_dinner **dinner, int philos_num)
{
    int i;

    i = 0;
    while (i < philos_num)
    {
        pthread_mutex_destroy((*(*dinner)->philos[i]->left_fork));
        free((*dinner)->philos[i]);
        free((*dinner)->table_forks[i]);
        i++;
    }
    free(*dinner);
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
    free(time);
    return (total);
}

void    *dine(void *arg)
{
    t_philo     *philo;
    size_t      time;
    int         n;

    philo = (t_philo*)arg;
    n = 0;
    while (n < 3)
    {
        pthread_mutex_lock(*(philo->left_fork));
        pthread_mutex_lock(*(philo->right_fork));
        printf("Philo %d EAT - %ld - %ld\n", philo->id, philo->time_to_eat, get_current_time());
        if (!philo->last_meal)
            philo->init_time = get_current_time();
        usleep(philo->time_to_eat);
        philo->last_meal = get_current_time();
        pthread_mutex_unlock(*(philo->left_fork));
        pthread_mutex_unlock(*(philo->right_fork));
        time = get_current_time();
        printf("Philo %d SLEEP - %ld - %ld\n", philo->id, philo->time_to_sleep, time);
        usleep(philo->time_to_sleep);
        time = get_current_time();
        printf("Philo %d THINK - %d - %ld\n", philo->id, 1000000, time);
        n++;
    }
    return (NULL);
}

int main(void)
{
    t_dinner    *dinner;
    int         philos_num;
    int         i;

    i = 0;
    philos_num = 2;         //NEEDS TO BE DINAMIC!
    dinner = malloc(sizeof(t_dinner));
    init_dinner(&dinner, philos_num);
    while (i < dinner->philos_num)
    {
        dinner->philos[i] = malloc(sizeof(t_philo));
        init_philo(&dinner->philos[i], &dinner->table_forks, i, philos_num);
        if (pthread_create(&dinner->philos[i]->thread, NULL, dine, (void*)dinner->philos[i]) != 0)
            return (1);
        dinner->idx++;
        i++;
    }
   i = 0;
    while (i < philos_num)
    {
        if (pthread_join(dinner->philos[i]->thread, NULL) != 0)
            return (2);
       i++;
    }
    clear(&dinner, dinner->philos_num);
    exit(0);
}
