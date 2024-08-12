/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:59:16 by root              #+#    #+#             */
/*   Updated: 2024/08/12 13:47:29 by root             ###   ########.fr       */
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
    pthread_t       life_checker;
    pthread_mutex_t *table_forks[TABLE_SIZE];
    pthread_mutex_t *halt_mutex;
    t_bool          halt;
    t_time          *time;
    size_t          init_time;
    size_t          time_to_die;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    int             total_meals;
    t_bool          infinite_dinner;
}               t_dinner;

typedef struct s_philo
{
    pthread_t   thread;
    int         id;
    int         meal_counter;
    size_t      last_meal;
    size_t      init_time;
    size_t      time_of_death;
    t_bool      halt;
    int         left_fork;
    int         right_fork;
    t_dinner    *dinner;
}               t_philo;

t_dinner    *init_dinner(int philos_num, int meals, size_t time_eat, size_t time_sleep);
t_philo     *init_philo(t_dinner **dinner, int id, int n);
void        handle_thread(t_philo **philo);
void        lock_forks(t_dinner **dinner, t_philo **philo);
void        unlock_forks(t_dinner **dinner, int left, int right);
size_t      get_current_time(void);
size_t      get_dinner_time(t_dinner **dinner, size_t time);
t_bool      shall_halt(t_dinner **dinner, t_philo **philo);
void        clear(t_philo *(*philos)[64]);

#endif
