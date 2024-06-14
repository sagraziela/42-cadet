/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:58:14 by root              #+#    #+#             */
/*   Updated: 2024/05/16 07:28:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	balance = 0;

int	read_balance(void)
{
	usleep(250000);
	return (balance);
}
void    *my_func(void *var)
{
    (void)var;
    sleep(2);
    printf("Entered my_func\n");
    return (NULL);
}

void    *my_func2(void *var)
{
    (void)var;
    sleep(2);
    printf("ENTERED MY_FUNC\n");
    return (NULL);
}

int main(void)
{
    pthread_t thrd1;
    pthread_t thrd2;
    pthread_mutex_t mutex;

    printf("Before thread\n");
    pthread_create(&thrd1, NULL, my_func, NULL);
    pthread_join(thrd1, NULL);
    pthread_create(&thrd2, NULL, my_func2, NULL);
    pthread_join(thrd2, NULL);
    printf("After thread\n");
    exit(0);
}
