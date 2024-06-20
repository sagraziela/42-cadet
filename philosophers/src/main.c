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
    //printf("%s", asctime(info));
    t = tval.tv_sec;
    info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y - %H:%M:%S\n", info);
    printf("%s", buffer);
}

void    *my_func()
{
    int i;

    i = 0;
    while (i++ < 1)
    {
        pthread_mutex_lock(&mutex);
        printf("EAT - ");
        get_current_time();
        sleep(5);
        printf("THINK - ");
        get_current_time();
        sleep(5);
        printf("SLEEP\n");
        get_current_time();
        pthread_mutex_unlock(&mutex);
    }
    return (NULL);
}

int main(void)
{
    pthread_t philo1;
    int     i;
    int     n_philo;

    i = 1;
    n_philo = 1;
    pthread_mutex_init(&mutex, NULL);
    while (i <= n_philo)
    {
        // CREATE LIST WITH THE NUMBERS OF PIHLOSOPHERS PASSED AS ARGUMENT
        if (pthread_create(&philo1, NULL, my_func, NULL) != 0)
            return (1);
        if (pthread_join(philo1, NULL) != 0)
            return (2);
        i++;
    }
    exit(0);
}
