#include "../includes/philo.h"

void    init_philo(t_philo **philo, pthread_mutex_t *(*table_forks)[TABLE_SIZE], int id, int n)
{
        (*philo)->id = id;
        (*philo)->time_to_eat = 3000000;
        (*philo)->time_to_sleep = 2000000;
        (*philo)->must_stop = FALSE;
        (*philo)->last_meal = 0;
        (*philo)->left_fork = &(*table_forks)[id];
        if (id == n - 1)
                (*philo)->right_fork = &(*table_forks)[0];
        else
                (*philo)->right_fork = &(*table_forks)[id + 1];
}


void    init_dinner(t_dinner **dinner, int philos_num)
{
        int     i;

        i = 0;
        (*dinner)->philos_num = philos_num;
        (*dinner)->idx = 0;
        (*dinner)->dead_flag = FALSE;
        (*dinner)->total_meals = 3;           //NEEDS TO BE DINAMIC!
        (*dinner)->philos[0] = NULL;
        while (i < philos_num)
        {
                //(*dinner)->philos[i] = malloc(sizeof(t_philo));
                (*dinner)->table_forks[i] = malloc(sizeof(pthread_mutex_t));
                pthread_mutex_init((*dinner)->table_forks[i], NULL);
                i++;
        }
}
