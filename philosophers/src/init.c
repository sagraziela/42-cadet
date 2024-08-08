#include "../includes/philo.h"

void    *check_if_alive(void *arg)
{
        t_philo *philo;
        size_t  time;
        int     i;

        philo = (t_philo*)arg;
        while (TRUE)
        {
                i = 0;
                time = get_current_time();
                while (philo[i]->id <= philo[i]->dinner->philos_num)
                {
                        if (time > philo[i]->time_to_die)
                                printf("PHILO %d IS DEeeAaD 💀\n", (*philo)->id);
                }
                usleep(10000000);
        }
}

void    init_philo(t_philo **philo, int id, int n, size_t time_die)
{
        (*philo)->id = id;
        (*philo)->init_time = get_current_time();
        (*philo)->time_to_die = (*philo)->init_time + time_die;      //NEEDS TO BE DINAMIC
        (*philo)->must_stop = FALSE;
        (*philo)->last_meal = 0;
        (*philo)->left_fork = id - 1;
        if (id == n)
                (*philo)->right_fork = 0;
        else
                (*philo)->right_fork = id;
        //USAR DETACH PARA MONITORAR SE O PHILO ESTÁ VIVO
        //FAZER UMA PARA O PROGRAMA INTEIRO OU UMA PARA CADA PHILO??
        if (id == n)
        {
                if (pthread_create(&(*philo)->dinner->life_checker, NULL, check_if_alive, (void*)philo) != 0)
                        return (1);
                pthread_detach((*philo)->dinner->life_checker);
        }
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
