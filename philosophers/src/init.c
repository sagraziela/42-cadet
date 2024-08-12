#include "../includes/philo.h"

t_philo *init_philo(t_dinner **dinner, int id, int n)
{
        t_philo *philo;

        philo = malloc(sizeof(t_philo));
        if (!philo)
                return (NULL);
        philo->id = id;
        philo->time_of_death = (*dinner)->init_time + (*dinner)->time_to_die;
        philo->last_meal = 0;
        philo->halt = FALSE;
        philo->dinner = *dinner;
        philo->left_fork = id - 1;
        if (id == n)
                philo->right_fork = 0;
        else
                philo->right_fork = id;
        return (philo);
}


t_dinner    *init_dinner(int philos_num, int meals, size_t time_eat, size_t time_sleep)
{
        t_dinner        *dinner;
        int             i;

        i = 0;
        dinner = malloc(sizeof(t_dinner));
        if (!dinner)
                return (NULL);
        dinner->philos_num = philos_num;
        dinner->init_time = get_current_time();
        dinner->time_to_eat = time_eat * 1000;
        dinner->time_to_sleep = time_sleep * 1000;
        dinner->total_meals = meals;
        dinner->infinite_dinner = FALSE;
        dinner->halt = FALSE;
        dinner->halt_mutex = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(dinner->halt_mutex, NULL);
        while (i < philos_num)
        {
                dinner->table_forks[i] = malloc(sizeof(pthread_mutex_t));
                pthread_mutex_init(dinner->table_forks[i], NULL);
                i++;
        }
        return (dinner);
}
