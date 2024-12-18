/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:05:49 by saberton          #+#    #+#             */
/*   Updated: 2024/11/05 17:03:34 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "colors.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define ORANGE "\e[38;5;214m"

# define WRONG_ARGS "Wrong number of args\n"
# define EXEMPLE "Write something like that : ./philo 5 800 200 100 (100)\n"
# define FOR_WHAT "arg[1] for : number_of_philosopher\narg[2] for : \
time_to_die\narg[3] for : time_to_eat\narg[4] for : time_to_sleep\n(OPTIONNAL)\n\
arg[5] for : number_of_times_each_philosopher_must_eat\n"

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}		t_philo_status;

typedef struct s_philo
{
	int				seat;
	int				nb_meals;
	long			last_meal;
	struct s_philo	*left;
	struct s_philo	*right;
	struct s_table	*table;
	pthread_t		thread;
	t_philo_status	status;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	nb_meals_mutex;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	last_meal_mutex;
}					t_philo;

typedef struct s_table
{
	int				nb_philo;
	long			start;
	long			death_time;
	long			meal_time;
	long			sleep_time;
	long			meals;
	struct s_philo	*first;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	print_mutex;
	int				isdead;
}					t_table;

void				ft_bzero(void *s, size_t n);
void				print(int timestamp_in_ms, char *str, t_philo *philo);
void				*routine(void *tab);
void				ft_usleep(size_t milliseconds, t_philo *philo);
void				exit_prog(t_table *table);
int					check_args(char *str, int nb);
int					init_table(char **av, t_table *table);
int					is_dead(t_philo *philo);
int					checkvarisdead(t_table *table);
long long			timestamp(void);

#endif