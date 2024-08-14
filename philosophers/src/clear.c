/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:48:43 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/14 14:49:26 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void    clear_table_forks(t_dinner **dinner)
{
    int i;

    i = 0;
    while (i < (*dinner)->philos_num)
    {
        pthread_mutex_destroy(&(*dinner)->table_forks[i]);
        i++;
    }
    free((*dinner)->table_forks);
    return ;
}

void    clear(t_philo **philos)
{
    int i;

    i = 0;
    clear_table_forks(&philos[i]->dinner);
    pthread_mutex_destroy(philos[i]->dinner->stop_mutex);
    pthread_mutex_destroy(philos[i]->dinner->print_mutex);
    pthread_mutex_destroy(philos[i]->dinner->eat_mutex);
    free(philos[i]->dinner->stop_mutex);
    free(philos[i]->dinner->print_mutex);
    free(philos[i]->dinner->eat_mutex);
    free(philos[i]->dinner);
    while (philos[i] != NULL)
    {
        free(philos[i]);
        i++;
    }
    free(philos);
    return ;
}
