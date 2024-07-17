#include "../includes/philo.h"

t_philo init_philo(pthread_mutex_t (*table_forks)[64], int id, int n)
{
        t_philo philo;

        philo.id = id;
        philo.time_to_eat = 3000000;
        philo.time_to_sleep = 2000000;
        philo.must_stop = FALSE;
        philo.last_meal = 0;
        // philo.forks = malloc(sizeof(t_forks));
        // philo.forks->left_fork = table_forks[id];
        // if (id == n - 1)
        //         philo.forks->right_fork = &(*table_forks)[0];
        // else
        //         philo.forks->right_fork = &(*table_forks)[id + 1];
        return (philo);
}


void    init_dinner(t_dinner **dinner, int philos_num)
{
        int     i;

        i = 0;
        while (i < philos_num)
        {
                pthread_mutex_init(&(*dinner)->table_forks[i], NULL);
                i++;
        }
}
