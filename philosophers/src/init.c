#include "../includes/philo.h"

t_philo **init_philo(t_dinner **dinner, int num)
{
    t_philo     **philo;
    int         i;

    philo = (t_philo **)malloc(sizeof(t_philo*) * num);
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
            philo[i]->halt = FALSE;
            philo[i]->dinner = *dinner;
            philo[i]->left_fork = i;
            if (i + 1 == num)
                    philo[i]->right_fork = 0;
            else
                    philo[i]->right_fork = philo[i]->id;
            i++;
       }
        return (philo);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

t_bool	ft_isnumeric(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
	}
	return (TRUE);
}

long	ft_atoi(const char *nptr)
{
	int	i;
	long	sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if ((nptr[i] == '+'))
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	return (res * sign);
}

t_bool  args_are_valid(int argc, char **argv)
{
        int     i;
        long    temp;

        i = 0;
        while (++i < argc)
	{
		temp = ft_atoi(argv[i]);
		if (!ft_isnumeric(argv[i]) || (temp > INT_MAX || temp < 0))
                {
                        //print_error();
			return (FALSE);
                }
	}
        return (TRUE);
}

t_bool  handle_args(int argc, char *argv[], t_dinner **dinner)
{
        if (!args_are_valid(argc, argv))
                return (FALSE);
        (*dinner)->philos_num = ft_atoi(argv[1]);
        (*dinner)->time_to_die = ft_atoi(argv[2]) * 1000;
        (*dinner)->time_to_eat = ft_atoi(argv[3]) * 1000;
        (*dinner)->time_to_sleep = ft_atoi(argv[4]) * 1000;
        if (argc == 6)
        {
                (*dinner)->total_meals = ft_atoi(argv[5]);
                (*dinner)->infinite_dinner = FALSE;
        }
        else
        {
                (*dinner)->total_meals = 0;
                (*dinner)->infinite_dinner = TRUE;
        }
        return (TRUE);
}

t_dinner    *init_dinner(int argc, char **argv)
{
        t_dinner        *dinner;
        int             i;

        dinner = malloc(sizeof(t_dinner));
        if (!dinner)
                return (NULL);
        if (!handle_args(argc, argv, &dinner))
        {
                free(dinner);
                return (NULL);
        }
        dinner->init_time = get_current_time();
        dinner->meals_had = 0;
        dinner->halt = FALSE;
        dinner->halt_mutex = malloc(sizeof(pthread_mutex_t));
        dinner->print_mutex = malloc(sizeof(pthread_mutex_t));
        dinner->eat_mutex = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(dinner->halt_mutex, NULL);
        pthread_mutex_init(dinner->print_mutex, NULL);
        pthread_mutex_init(dinner->eat_mutex, NULL);
        dinner->table_forks = malloc(dinner->philos_num * sizeof(pthread_mutex_t));
        i = -1;
        while (++i < dinner->philos_num)
                pthread_mutex_init(&dinner->table_forks[i], NULL);
        return (dinner);
}
