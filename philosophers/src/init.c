#include "../includes/philo.h"

t_philo **init_philo(t_dinner **dinner, int num)
{
        t_philo     **philo;
        int         i;

        philo = (t_philo **)malloc(sizeof(t_philo*) * (num + 1));
        if (!philo)
                return (NULL);
        i = 0;
        while (i < num)
        {
                philo[i] = malloc(sizeof(t_philo));
                if (!philo[i])
                return (NULL);
                philo[i]->id = i + 1;
                philo[i]->time_of_death = (*dinner)->init_time + (*dinner)->time_to_die;
                philo[i]->last_meal = 0;
                philo[i]->dinner = *dinner;
                philo[i]->left_fork = i;
                if (i + 1 == num)
                        philo[i]->right_fork = 0;
                else
                        philo[i]->right_fork = philo[i]->id;
                i++;
        }
        philo[num] = NULL;
        return (philo);
}

t_dinner    *init_dinner(int argc, char **argv)
{
        t_dinner        *dinner;
        int             i;

        dinner = malloc(sizeof(t_dinner));
        if (!dinner)
                return (NULL);
        if (!handle_args(argc, argv, &dinner) || dinner->philos_num == 0)
        {
                free(dinner);
                return (NULL);
        }
        dinner->init_time = get_current_time();
        dinner->meals_had = 0;
        dinner->stop = FALSE;
        dinner->stop_mutex = malloc(sizeof(pthread_mutex_t));
        dinner->print_mutex = malloc(sizeof(pthread_mutex_t));
        dinner->eat_mutex = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(dinner->stop_mutex, NULL);
        pthread_mutex_init(dinner->print_mutex, NULL);
        pthread_mutex_init(dinner->eat_mutex, NULL);
        dinner->table_forks = malloc(dinner->philos_num * sizeof(pthread_mutex_t));
        i = -1;
        while (++i < dinner->philos_num)
                pthread_mutex_init(&dinner->table_forks[i], NULL);
        return (dinner);
}
