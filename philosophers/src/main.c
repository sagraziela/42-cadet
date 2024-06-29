/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/06/29 16:53:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t mutex;

void    get_current_time(void)
{
    struct  timeval tval;
    time_t  t;
    struct  tm *info;
    char    buffer[64];
    
    gettimeofday(&tval, NULL);
    t = tval.tv_sec;
    info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", info);
    printf("%s\n", buffer);
}

void   get_action_time(void)
{
    // int     total;
    // char    *init_time;

    // total = 0;
    // init_time = get_current_time();
}

void    *dinner(void *arg)
{
    t_philo *philo;
    int     i;

    philo = (t_philo*)arg;
    i = 0;
    while (i < 3)
    {
        if (!philo->must_stop)
        {
            pthread_mutex_lock(&mutex);
            printf("Philo %d EAT - %ld -", philo->id, philo->time_to_eat);
            get_current_time();
            usleep(philo->time_to_eat);
            pthread_mutex_unlock(&mutex);
            philo->must_stop = TRUE;
        }
        printf("Philo %d SLEEP - %ld - ", philo->id, philo->time_to_sleep);
        get_current_time();
        usleep(philo->time_to_sleep);
        printf("Philo %d THINK - %d - ", philo->id, 1000000);
        get_current_time();
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
