#include "../includes/philo.h"

void    init_philo(t_philo philo[64], int philos_num)
{
        philo->id = philos_num;
        philo->time_to_eat = 3000000;
        philo->time_to_sleep = 2000000;
        philo->must_stop = FALSE;
}
