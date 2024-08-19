/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:52:25 by root              #+#    #+#             */
/*   Updated: 2024/08/19 13:59:33 by gde-souz         ###   ########.fr       */
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

static void	acknowledge_first_death(
	t_dinner **dinner, t_philo **philo, long time)
{
	(*dinner)->first_death = FALSE;
	printf("%s%ld %d died.%s\n", BRED, time, (*philo)->id, COLOUR_RESET);
}

static void	increment_meals_had(
	t_dinner **dinner, t_philo **philo, long time)
{
	(*dinner)->meals_had++;
	printf("%s%ld %d is eating.%s\n",
		YELLOW, time, (*philo)->id, COLOUR_RESET);
}

void	print_action(t_philo **philo, t_dinner **dinner, char *action)
{
	size_t	time;

	pthread_mutex_lock((*dinner)->print_mutex);
	time = get_dinner_time(dinner, get_current_time());
	if (!ft_strcmp(action, FORK) && !must_stop(dinner))
		printf("%s%ld %d has taken a fork.%s\n",
			GREEN, time, (*philo)->id, COLOUR_RESET);
	if (!ft_strcmp(action, EAT) && !must_stop(dinner))
		increment_meals_had(dinner, philo, time);
	if (!ft_strcmp(action, SLEEP) && !must_stop(dinner))
		printf("%s%ld %d is sleeping.%s\n",
			LILAC, time, (*philo)->id, COLOUR_RESET);
	if (!ft_strcmp(action, THINK) && !must_stop(dinner))
		printf("%s%ld %d is thinking.%s\n",
			BLUE, time, (*philo)->id, COLOUR_RESET);
	if (!ft_strcmp(action, DIE) && (*dinner)->first_death == TRUE)
		acknowledge_first_death(dinner, philo, time);
	pthread_mutex_unlock((*dinner)->print_mutex);
	return ;
}

void	print_error(void)
{
	printf("%sThe program must be executed with the following parameters.%s\n",
		LRED, COLOUR_RESET);
	printf("%sParameters shall be given in miliseconds.\n\n%s",
		LRED, COLOUR_RESET);
	printf("%s./philo [%snumber_of_philosophers%s]", BRED, BBLUE, LRED);
	printf("%s [%stime_to_die%s] [%stime_to_eat%s] [%stime_to_sleep%s]%s\n\n",
		LRED, BBLUE, LRED, BBLUE, LRED, BBLUE, LRED, COLOUR_RESET);
	printf("%s*You may also determine the [%s", LRED, COLOUR_RESET);
	printf("%snbr_of_times_each_philo_must_eat%s] as a 5th parameter.%s\n",
		BBLUE, LRED, COLOUR_RESET);
}
