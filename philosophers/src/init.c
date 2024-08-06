#include "../includes/philo.h"

void    init_philo(t_philo **philo, int id, int n, t_dinner **dinner)
{
        (void)dinner;
        (*philo)->id = id;
        //(*philo)->dinner = &(*dinner);
        (*philo)->init_time = 0;
        (*philo)->time_to_die = get_current_time() + 3000;      //NEEDS TO BE DINAMIC
        (*philo)->must_stop = FALSE;
        (*philo)->last_meal = 0;
        (*philo)->left_fork = id;
        if (id == n - 1)
                (*philo)->right_fork = 0;
        else
                (*philo)->right_fork = id + 1;
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
        dinner->idx = 0;
        dinner->start = get_current_time();
        dinner->time_to_eat = time_eat;
        dinner->time_to_sleep = time_sleep;
        dinner->dead_flag = FALSE;
        dinner->total_meals = meals;
        while (i < philos_num)
        {
                dinner->table_forks[i] = malloc(sizeof(pthread_mutex_t));
                pthread_mutex_init(dinner->table_forks[i], NULL);
                i++;
        }
        return (dinner);
}
