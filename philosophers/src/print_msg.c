/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:52:25 by root              #+#    #+#             */
/*   Updated: 2024/08/14 14:51:03 by gde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

void    print_action(t_philo **philo, t_dinner **dinner, char *action)
{
    size_t  time;

    pthread_mutex_lock((*dinner)->print_mutex);
    time = get_dinner_time(dinner, get_current_time());
    if (!ft_strcmp(action, L_FORK) && !must_stop(dinner, philo))
        printf("%s%ld %d has taken L fork.%s\n", GREEN, time, (*philo)->id, COLOUR_RESET);
    if (!ft_strcmp(action, R_FORK) && !must_stop(dinner, philo))
        printf("%s%ld %d has taken R fork.%s\n", GREEN, time, (*philo)->id, COLOUR_RESET);
    if (!ft_strcmp(action, EAT) && !must_stop(dinner, philo))
        printf("%s%ld %d is eating.%s\n", YELLOW, time, (*philo)->id, COLOUR_RESET);
    if (!ft_strcmp(action, SLEEP) && !must_stop(dinner, philo))
        printf("%s%ld %d is sleeping.%s\n", LILAC, time, (*philo)->id, COLOUR_RESET);
    if (!ft_strcmp(action, THINK) && !must_stop(dinner, philo))
        printf("%s%ld %d is thinking.%s\n", BLUE, time, (*philo)->id, COLOUR_RESET);
    if (!ft_strcmp(action, DIE))
        printf("%s%ld %d died.%s\n", BRED, time, (*philo)->id, COLOUR_RESET);
    pthread_mutex_unlock((*dinner)->print_mutex);
    return ;
}

void    print_error(void)
{
    printf("%sThe program must be executed with the following parameters, which shall be given in miliseconds:%s\n\n", LRED, COLOUR_RESET);
    printf("%s./philo [%snumber_of_philosophers%s] [%stime_to_die%s] [%stime_to_eat%s] [%stime_to_sleep%s]%s\n\n", BRED, BBLUE, LRED, BBLUE, LRED, BBLUE, LRED, BBLUE, LRED, COLOUR_RESET);
    printf("%s*You may also determine the [%snumber_of_times_each_philosopher_must_eat%s] as a 5th parameter.%s\n", LRED, BBLUE, LRED, COLOUR_RESET);
}
