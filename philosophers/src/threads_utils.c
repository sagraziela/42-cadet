/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:41:40 by gde-souz          #+#    #+#             */
/*   Updated: 2024/08/14 14:42:44 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool  must_stop(t_dinner **dinner, t_philo **philo)
{
    t_bool temp;
    
    (void)philo;
    pthread_mutex_lock((*dinner)->stop_mutex);
    temp = (*dinner)->stop;
    pthread_mutex_unlock((*dinner)->stop_mutex);
    return (temp);
}

void    to_stop(t_dinner **dinner)
{
    pthread_mutex_lock((*dinner)->stop_mutex);
    (*dinner)->stop = TRUE;
    pthread_mutex_unlock((*dinner)->stop_mutex);
    return ;
}

t_bool  check_if_alive(t_philo **philo)
{
    size_t time;
    
    time = get_current_time();
    if (time >= (*philo)->time_of_death && !must_stop(&(*philo)->dinner, philo))
    {
        to_stop(&(*philo)->dinner);
        print_action(philo, &(*philo)->dinner, DIE);
        return (FALSE);
    }
    return (TRUE);
}