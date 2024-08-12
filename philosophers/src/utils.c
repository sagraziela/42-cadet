/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:52:25 by root              #+#    #+#             */
/*   Updated: 2024/08/12 14:38:56 by root             ###   ########.fr       */
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
    pthread_mutex_destroy((*philos)[i]->dinner->halt_mutex);
    free((*philos)[i]->dinner->halt_mutex);
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
    size_t  total;
    
    if (gettimeofday(&tval, NULL) != 0)
    {
        printf("Error getting timestamp.\n");
        return (0);
    }
    total = (tval.tv_sec * 1000000) + tval.tv_usec;
    return (total);
}

size_t  get_dinner_time(t_dinner **dinner, size_t time)
{
    return ((time - (*dinner)->init_time) / 1000);
}
