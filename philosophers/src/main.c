/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/08/06 19:32:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *dine(void *arg)
{
    t_philo     *philo;
    int         n;

    philo = (t_philo*)arg;
    n = 0;
    while (n < philo->dinner->total_meals)
    {
        handle_thread(&philo);
        n++;
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
    philos_num = 3;         //NEEDS TO BE DINAMIC!
    dinner = init_dinner(philos_num, 3, 3000, 2000);
    dinner->time_to_die = 5000;
    while (i < philos_num)
    {
        philos[i] = malloc(sizeof(t_philo));
        init_philo(&philos[i], i + 1, philos_num, dinner->time_to_die);
        philos[i]->dinner = dinner;
        if (pthread_create(&philos[i]->thread, NULL, dine, (void*)philos[i]) != 0)
            return (1);
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
