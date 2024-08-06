/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/08/06 16:25:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    clear(t_philo *(*philos)[64])
{
    int i;
    int philos_num;

    i = 0;
    philos_num = (*philos)[0]->dinner->philos_num;
    while (i < philos_num)
    {
        pthread_mutex_destroy((*philos)[0]->dinner->table_forks[i]);
        free((*philos)[0]->dinner->table_forks[i]);
        i++;
    }
    i = 0;
    free((*philos)[i]->dinner);
    while (i < philos_num)
    {
        free((*philos)[i]);
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
    free(time);
    return (total);
}

void    handle_mutexes(t_philo **philo)
{
    t_dinner    **dinner;
    size_t      time;

    dinner = &((*philo)->dinner);
    pthread_mutex_lock((*dinner)->table_forks[(*philo)->left_fork]);
    pthread_mutex_lock((*dinner)->table_forks[(*philo)->right_fork]);
    time = get_current_time();
    printf("Philo %d EAT 🍽 - %ld - %ld\n", (*philo)->id, (*dinner)->time_to_eat, time);
    if (!(*philo)->last_meal)
        (*philo)->init_time = get_current_time();
    usleep((*dinner)->time_to_eat);
    pthread_mutex_unlock((*dinner)->table_forks[(*philo)->left_fork]);
    pthread_mutex_unlock((*dinner)->table_forks[(*philo)->right_fork]);
    time = get_current_time();
    (*philo)->last_meal = time;
    (*philo)->time_to_die = time + 3000;       //NEEDS TO BE DINAMIC
    printf("Philo %d SLEEP 💤 - %ld - %ld\n", (*philo)->id, (*dinner)->time_to_sleep, time);
    usleep((*dinner)->time_to_sleep);
    time = get_current_time();
    printf("Philo %d THINK 🤔 - %d - %ld\n", (*philo)->id, 1000000, time);
}

void    *dine(void *arg)
{
    t_philo     *philo;
    size_t      time;
    int         n;

    philo = (t_philo*)arg;
    n = 0;
    while (n < philo->dinner->total_meals)
    {
        time = get_current_time();
        if (time < philo->time_to_die)
        {
            handle_mutexes(&philo);
            n++;
        }
        else
        {
            printf("PHILO %d IS DEAD :(\n", philo->id);
            break ;
        }
    }
    return (NULL);
}

int main(void)
{
    t_dinner    *dinner;
    t_philo     *philos[TABLE_SIZE];
    int         philos_num;
    int         i;

    i = 0;
    philos_num = 2;         //NEEDS TO BE DINAMIC!
    dinner = init_dinner(philos_num, 3, 3000000, 2000000);
    while (i < philos_num)
    {
        philos[i] = malloc(sizeof(t_philo));
        init_philo(&philos[i], i, philos_num, &dinner);
        philos[i]->dinner = dinner;
        if (pthread_create(&philos[i]->thread, NULL, dine, (void*)philos[i]) != 0)
            return (1);
        philos[i]->dinner->idx++;
        i++;
    }
   i = 0;
    while (i < philos_num)
    {
        if (pthread_join(philos[i]->thread, NULL) != 0)
            return (2);
       i++;
    }
    clear(&philos);
    exit(0);
}
