/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:59:16 by root              #+#    #+#             */
/*   Updated: 2024/08/23 15:09:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define FORK "fork"
# define EAT "eat"
# define SLEEP "sleep"
# define THINK "think"
# define DIE "die"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>
# include <limits.h>
# include "./ansi_color_codes.h"

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}		t_bool;

typedef struct s_dinner
{
	int				philos_num;
	pthread_mutex_t	*table_forks;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_mutex;
	t_bool			stop;
	t_bool			first_death;
	size_t			init_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				philos_full;
	int				total_meals;
	t_bool			infinite_dinner;
}		t_dinner;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	size_t		last_meal;
	size_t		init_time;
	size_t		time_of_death;
	int			meals_had;
	int			left_fork;
	int			right_fork;
	t_dinner	*dinner;
}		t_philo;

t_dinner	*init_dinner(int argc, char **argv);
t_philo		**init_philo(t_dinner **dinner, int num);
t_bool		handle_args(int argc, char *argv[], t_dinner **dinner);
void		handle_eat(t_dinner **dinner, t_philo **philo);
void		handle_sleep(t_dinner **dinner, t_philo **philo);
t_bool		lock_forks(t_dinner **dinner, t_philo **philo);
size_t		get_current_time(void);
size_t		get_dinner_time(t_dinner **dinner, size_t time);
void		to_stop(t_dinner **dinner);
t_bool		must_stop(t_dinner **dinner);
int			choose_forks(t_philo **philo, int side);
t_bool		check_if_alive(t_philo **philo);
void		print_action(t_philo **philo, t_dinner **dinner, char *action);
void		print_error(void);
void		clear(t_philo **philos);

#endif
