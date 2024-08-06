/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:59:16 by root              #+#    #+#             */
/*   Updated: 2024/08/06 16:05:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TABLE_SIZE 64
# define EMOJI_DEAD 💀
// # define EMOJI_FORK "\U+1F374"
// # define EMOJI_EAT "\U1F37D"
// # define EMOJI_SLEEP "\U+1F4A4"
// # define EMOJI_THINK "\U+1F914"

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

// typedef struct s_forks
// {
//     pthread_mutex_t **left_fork;
//     pthread_mutex_t **right_fork;
// }               t_forks;

typedef struct s_time
{
    size_t  hour;
    size_t  min;
    size_t  sec;
    size_t  total_millisec;
}               t_time;

typedef struct s_dinner
{
    int             philos_num;
    int             idx;
    t_bool          dead_flag;
    pthread_mutex_t *table_forks[TABLE_SIZE];
    t_time          *time;
    size_t          start;
    size_t          end;
    size_t          time_to_die;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    int             total_meals;
    //pthread_mutex_t mutex_eat;
}               t_dinner;

typedef struct s_philo
{
    pthread_t   thread;
    int         id;
    t_bool      must_stop;
    int         meal_counter;
    size_t      last_meal;
    size_t      init_time;
    size_t      time_to_die;
    int         left_fork;
    int         right_fork;
    t_dinner    *dinner;
}               t_philo;


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

t_dinner    *init_dinner(int philos_num, int meals, size_t time_eat, size_t time_sleep);
void        init_philo(t_philo **philo, int id, int n, t_dinner **dinner);
size_t      get_current_time(void);

#endif
