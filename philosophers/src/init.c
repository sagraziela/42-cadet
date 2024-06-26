#include "../includes/philo.h"

void    init_program(t_program **program)
{
    *program = malloc(sizeof(t_program));
    (*program)->dead_flag = FALSE;
    (*program)->philos = NULL;
}

void    new_philo(t_philo **philo)
{
    t_philo *new_philo;
    t_philo *head;
    int     new_id;

    head = *philo;
    if (*philo)
    {
        while ((*philo)->next)
            *philo = (*philo)->next;
        new_id = (*philo)->id + 1;
    }
    else
        new_id = 1;
    new_philo = malloc(sizeof(t_philo));
    if (!new_philo)
        return ;
    new_philo->id = new_id;
    new_philo->time_to_eat = 3000000;
    new_philo->time_to_sleep = 2000000;
    new_philo->must_stop = FALSE;
    new_philo->next = NULL;
    if (*philo)
    {
        (*philo)->next = new_philo;
        *philo = head;
    }
    else
        *philo = new_philo;
}