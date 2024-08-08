/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:52:25 by root              #+#    #+#             */
/*   Updated: 2024/08/06 17:53:15 by root             ###   ########.fr       */
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

size_t  to_micro(size_t num)
{
    return (num * 1000);
}
