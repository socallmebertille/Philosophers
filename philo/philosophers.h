/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:05:49 by saberton          #+#    #+#             */
/*   Updated: 2024/10/11 16:55:59 by saberton         ###   ########.fr       */
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

# define WRONG_ARGS "Wrong number of args\n"
# define EXEMPLE "Write something like that : ./philo 5 800 200 100 (100)\n"
# define FOR_WHAT \
	"arg[1] for : number_of_philosopher\narg[2] for :  \
time_to_die\narg[3] for :  time_to_eat\narg[4] for :  time_to_sleep\n(OPTIONNAL)\n\
arg[5] for : number_of_times_each_philosopher_must_eat\n"

typedef struct s_philo
{
	struct s_philo	*left;
	struct s_philo	*right;
	int				seat;
	int				fork;
	int				nb_meals;
	int				nb_sleep;
	int				nb_think;
}					t_philo;

typedef struct s_table
{
	struct s_philo	*first;
	int				nb_philo;
	int				nb_fork;
	int				death_time;
	int				meal_time;
	int				sleep_time;
	int				meals;
}					t_table;

void				ft_bzero(void *s, size_t n);
void				*routine(t_table *table);
int					exit_prog(t_table *table);
int					init_table(char **av, t_table *table);
long				ft_atol(const char *str);

#endif