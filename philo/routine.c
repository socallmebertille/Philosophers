/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:40 by saberton          #+#    #+#             */
/*   Updated: 2024/10/26 21:50:21 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&philo->status_mutex);
	pthread_mutex_lock(&philo->fork_mutex);
	print("has taken a fork", philo);
	if (table->nb_philo == 1)
	{
		philo->status = DIED;
		pthread_mutex_unlock(&philo->status_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		return ;
	}
	// pthread_mutex_lock(&philo->left->fork_mutex);
	philo->status = EATING;
	print(BLUE "is eating" RESET, philo);
	pthread_mutex_lock(&philo->nb_meals_mutex);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->status_mutex);
	pthread_mutex_unlock(&philo->nb_meals_mutex);
	usleep(table->meal_time * 1000);
	pthread_mutex_unlock(&philo->fork_mutex);
	// pthread_mutex_unlock(&philo->left->fork_mutex);
}

static void	sleeping(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = SLEEPING;
	if (philo->nb_meals == 0)
	{
		pthread_mutex_unlock(&philo->status_mutex);
		return ;
	}
	print("is sleeping", philo);
	philo->nb_sleep += 1;
	pthread_mutex_unlock(&philo->status_mutex);
	usleep(table->sleep_time * 1000);
}

static void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = THINKING;
	if (philo->nb_meals == 0)
	{
		pthread_mutex_unlock(&philo->status_mutex);
		return ;
	}
	print("is thinking", philo);
	philo->nb_think += 1;
	pthread_mutex_unlock(&philo->status_mutex);
}
// usleep(table->think_time * 1000); // Temps de réflexion

void	*routine(void *phi)
{
	t_philo		*philo;
	int			turn;

	turn = 1;
	philo = (t_philo *)phi;
	while (!everybody_has_eaten(philo->table))
	{
		// printf(YELLOW "turn n-%d\n" RESET, turn);
		if (has_anyone_died(philo->table))
			break ;
		eating(philo, philo->table);
		if (has_anyone_died(philo->table))
			break ;
		sleeping(philo, philo->table);
		if (has_anyone_died(philo->table))
			break ;
		thinking(philo);
		turn++;
	}
	return (NULL);
}
