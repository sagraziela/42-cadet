/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/07/10 19:42:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t mutex;

// void   time_in_milliseconds(char *str)
// {
//     t_time  *time;
//     size_t  total;
    
//     time = malloc(sizeof(t_time));
//     time.
// }

size_t    get_current_time(void)
{
    struct  timeval tval;
    time_t  t;
    struct  tm *info;
   // char    buffer[64];
    t_time  *time;
    size_t  total;
    
    gettimeofday(&tval, NULL);
    t = tval.tv_sec;
    info = localtime(&t);
   // strftime(buffer, sizeof(buffer), "%H", info);
    time = malloc(sizeof(t_time));
    time->hour = info->tm_hour * 60 * 60 * 1000;
    time->min = info->tm_min * 60 * 1000;
    time->sec = info->tm_sec * 1000;
    total = time->hour + time->min + time->sec;
    //printf("%ld\n", total);
    return (total);
}

void    *dinner(void *arg)
{
    t_philo *philo;
    size_t  time;
    int     i;

    philo = (t_philo*)arg;
    i = 0;
    while (i < 3)
    {
        if (!philo->must_stop)
        {
            pthread_mutex_lock(&mutex);
            printf("Philo %d EAT - %ld - %ld\n", philo->id, philo->time_to_eat, get_current_time());
            if (!philo->last_meal)
                philo->init_time = get_current_time();
            usleep(philo->time_to_eat);
            philo->last_meal = get_current_time();
            philo->must_stop = TRUE;
            pthread_mutex_unlock(&mutex);
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
    t_philo     philos[64];
    int         philos_num;
    int         i;

    i = 0;
    philos_num = 2;
    pthread_mutex_init(&mutex, NULL);
    while (i < philos_num)
    {
        init_philo(&(philos[i]), i);
        if (pthread_create(&philos[i].thread, NULL, dinner, (void*)&philos[i]) != 0)
            return (1);
        i++;
    }
   i = 0;
    while (i < philos_num)
    {
        if (pthread_join(philos[i].thread, NULL) != 0)
            return (2);
       i++;
    }
    exit(0);
}
