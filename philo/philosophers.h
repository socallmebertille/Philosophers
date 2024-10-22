/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:05:49 by saberton          #+#    #+#             */
/*   Updated: 2024/10/22 16:18:19 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define RESET "\e[0m"
# define RED "\e[1;91m"
# define GREEN "\e[1;92m"
# define PURPLE "\033[1;35m"
# define YELLOW "\e[1;93m"
# define ORANGE "\e[38;5;214m"
# define BLUE "\e[1;94m"

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
	// TAKE_FIRST_FORK,
	// TAKE_SECOND_FORK,
	DIED,
}		t_philo_status;

typedef struct s_philo
{
	int				seat;
	int				fork;
	int				nb_meals;
	int				nb_sleep;
	int				nb_think;
	struct s_philo	*left;
	struct s_philo	*right;
	pthread_t		thread;
	t_philo_status	status;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	status_mutex;
}					t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				nb_fork;
	int				death_time;
	int				meal_time;
	int				sleep_time;
	int				meals;
	struct s_philo	*first;
	pthread_mutex_t	table_mutex;
}					t_table;

void				ft_bzero(void *s, size_t n);
void				*routine(void *tab);
int					exit_prog(t_table *table);
int					init_table(char **av, t_table *table);
long				ft_atol(const char *str);

#endif