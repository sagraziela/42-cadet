/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/08/13 19:25:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *dine(void *arg)
{
    t_philo     *philo;
    t_dinner    **dinner;
    int         n;

    philo = (t_philo*)arg;
    dinner = &philo->dinner;
    n = 0;
    while ((!philo->dinner->infinite_dinner && n < philo->dinner->total_meals && !shall_halt(&philo->dinner, &philo)) ||
    (philo->dinner->infinite_dinner && !shall_halt(&philo->dinner, &philo)))
    {
        if (!shall_halt(dinner, &philo))
            handle_eat(dinner, &philo);
        if (!shall_halt(dinner, &philo))
            handle_sleep(dinner, &philo);
        n++;
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    t_dinner    *dinner;
    t_philo     **philos;
    int         philos_num;
    int         i;

    i = 0;
    philos_num = 2;
    dinner = init_dinner(argc, argv);
    if ((argc == 5 || argc == 6) && dinner)
    {
        philos = init_philo(&dinner, philos_num);
        while (i < philos_num)
        {
            pthread_create(&philos[i]->thread, NULL, dine, (void *)philos[i]);
            i++;
        }
        i = 0;
        while (i < philos_num)
        {
            pthread_join(philos[i]->thread, NULL);
            i++;
        }
        clear(philos);
        return (0);
    }
    print_error();
    return (1);
}
