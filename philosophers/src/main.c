/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/06/20 13:34:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	balance = 0;
pthread_mutex_t mutex;

void    *my_func()
{
    int i;

    i = 0;
    while (i++ < 1000000)
    {
        pthread_mutex_lock(&mutex);
        balance++;
        pthread_mutex_unlock(&mutex);
    }
    return (NULL);
}

int main(void)
{
    // t_list *list;
    // int     n_philo;
    // int     i;
    struct  timeval tval;
    time_t  t;
    struct  tm *info;
    //char    buffer[64];

    gettimeofday(&tval, NULL);
    t = tval.tv_sec;
    info = localtime(&t);
    printf("%s", asctime(info));
    // i = 1;
    // n_philo = atoi(argv[0]);
    // pthread_mutex_init(&mutex, NULL);
    // while (i <= n_philo)
    // {
    //     new_node();
    //     // CREATE LIST WITH THE NUMBERS OF PIHLOSOPHERS PASSED AS ARGUMENT
    //     if (pthread_create(&list->philo, NULL, my_func, NULL) != 0)
    //         return (1);
    //     if (pthread_join(&list->philo, NULL) != 0)
    //         return (2);
    //     i++;
    // }
    // printf("Balance: %d\n", balance);
    // exit(0);
}
