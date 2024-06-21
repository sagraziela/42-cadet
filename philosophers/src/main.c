/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/06/20 15:53:30 by root             ###   ########.fr       */
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
    strftime(buffer, sizeof(buffer), "%H:%M:%S\n", info);
    printf("%s", buffer);
}

void    new_philo(t_philo **philo)
{
    t_philo *new_philo;
    t_philo *head;
    int     new_id;

    if (!(*philo))
    {
        *philo = malloc(sizeof(t_philo));
        (*philo)->id = 1;
        (*philo)->next = NULL;
        return ;
    }
    head = *philo;
    while ((*philo)->next)
        *philo = (*philo)->next;
    new_id = (*philo)->id + 1;
    new_philo = malloc(sizeof(t_philo));
    if (!new_philo)
        return ;
    new_philo->id = new_id;
    new_philo->next = NULL;
    (*philo)->next = new_philo;
    *philo = head;
}

void    *my_func(void *philo)
{
    int id;

    id = ((t_philo*)philo)->id;
    pthread_mutex_lock(&mutex);
    printf("Philo %d EAT - ", id);
    get_current_time();
    usleep(3000000);
    printf("Philo %d SLEEP - ", id);
    get_current_time();
    usleep(3000000);
    printf("Philo %d THINK - ", id);
    get_current_time();
    usleep(3000000);
    pthread_mutex_unlock(&mutex);
    return (NULL);
}

int main(void)
{
    t_philo *philos_list;
    t_philo *temp;
    int     i;
    int     n_philo;

    i = 1;
    n_philo = 2;
    philos_list = NULL;
    pthread_mutex_init(&mutex, NULL);
    while (i <= n_philo)
    {
        new_philo(&philos_list);
        i++;
    }
    temp = philos_list;
    while (philos_list)
    {
        printf("ID: %d\n", philos_list->id);
        if (pthread_create(&philos_list->thread, NULL, my_func, (void*)philos_list) != 0)
            return (1);
        if (pthread_join(philos_list->thread, NULL) != 0)
            return (2);
        philos_list = philos_list->next;
    }
    philos_list = temp;
    exit(0);
}
