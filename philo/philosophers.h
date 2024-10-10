/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:05:49 by saberton          #+#    #+#             */
/*   Updated: 2024/10/09 22:56:35 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define RESET "\e[0m"
# define RED "\e[1;91m"
# define GREEN "\e[1;92m"
# define PURPLE "\033[1;35m"

typedef struct s_philo
{
	struct s_philo	*left;
	struct s_philo	*right;
	int				seat;
	int				fork;
}					t_philo;

typedef struct s_data
{
	struct s_philo	*first;
	int				nb_philo;
	int				nb_fork;
	int				death_time;
	int				meal_time;
	int				sleep_time;
	int				meals;
}					t_data;

#endif