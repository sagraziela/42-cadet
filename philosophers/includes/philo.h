/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:59:16 by root              #+#    #+#             */
/*   Updated: 2024/06/29 16:57:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>

typedef enum e_bool
{
    TRUE = 1,
    FALSE = 0
}           t_bool;

typedef struct s_forks
{
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
}               t_forks;

typedef struct s_philo
{
    pthread_t       thread;
    int             id;
    t_bool          must_stop;
    size_t          init_time;
    size_t          time_to_die;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    t_forks         *forks;
}               t_philo;

// typedef struct s_dine
// {
//     t_bool  dead_flag;
//     t_philo philos[64];
//     pthread_mutex_t mutex_eat;
// }               t_dine;

// typedef struct s_philo
// {
// 	pthread_t		thread;
// 	int				id;
// 	int				eating;
// 	int				meals_eaten;
// 	size_t			last_meal;
// 	size_t			time_to_die;
// 	size_t			time_to_eat;
// 	size_t			time_to_sleep;
// 	size_t			start_time;
// 	int				num_of_philos;
// 	int				num_times_to_eat;
// 	int				*dead;
// 	pthread_mutex_t	*r_fork;
// 	pthread_mutex_t	*l_fork;
// 	pthread_mutex_t	*write_lock;
// 	pthread_mutex_t	*dead_lock;
// 	pthread_mutex_t	*meal_lock;
// }					t_philo;

// typedef struct s_program
// {
// 	int				dead_flag;
// 	pthread_mutex_t	dead_lock;
// 	pthread_mutex_t	meal_lock;
// 	pthread_mutex_t	write_lock;
// 	t_philo			*philos;
// }					t_program;

void    init_philo(t_philo philo[64], int philos_num);
void    new_philo(t_philo **philo);

#endif
