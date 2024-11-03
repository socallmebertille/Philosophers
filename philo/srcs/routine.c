/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:40 by saberton          #+#    #+#             */
/*   Updated: 2024/11/03 05:23:18 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *philo)
{
	if (philo->table->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		print(timestamp() - philo->table->start, "has taken a fork", philo);
		return ;
	}
	if (philo->seat % 2 == 0)
	{
		pthread_mutex_lock(&philo->left->fork_mutex);
		pthread_mutex_lock(&philo->fork_mutex);
		print(timestamp() - philo->table->start, "has taken a fork", philo);
		print(timestamp() - philo->table->start, "has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(&philo->fork_mutex);
		pthread_mutex_lock(&philo->left->fork_mutex);
		print(timestamp() - philo->table->start, "has taken a fork", philo);
		print(timestamp() - philo->table->start, "has taken a fork", philo);
	}
}

static void	eating(t_philo *philo, t_table *table)
{
	if (philo->status != THINKING)
		return ;
	take_forks(philo);
	if (table->nb_philo == 1)
	{
		philo->status = DIED;
		ft_usleep(table->death_time, philo);
		print(timestamp() - philo->table->start, BRED "died" RESET, philo);
		philo->table->isdead = 1;
		pthread_mutex_unlock(&philo->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = EATING;
	print(timestamp() - philo->table->start, BGREEN "is eating" RESET, philo);
	pthread_mutex_lock(&philo->nb_meals_mutex);
	philo->nb_meals++;
	philo->last_meal = timestamp() - table->start;
	pthread_mutex_unlock(&philo->nb_meals_mutex);
	pthread_mutex_unlock(&philo->status_mutex);
	ft_usleep(table->meal_time, philo);
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->left->fork_mutex);
}

static void	sleeping(t_philo *philo, t_table *table)
{
	if (philo->status != EATING)
		return ;
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = SLEEPING;
	pthread_mutex_unlock(&philo->status_mutex);
	if (philo->nb_meals == 0)
	{
		ft_usleep(table->meal_time, philo);
		return ;
	}
	print(timestamp() - philo->table->start, "is sleeping", philo);
	ft_usleep(table->sleep_time, philo);
}

static void	thinking(t_philo *philo, t_table *table)
{
	if (philo->status != SLEEPING)
		return ;
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = THINKING;
	pthread_mutex_unlock(&philo->status_mutex);
	if (philo->nb_meals == 0)
	{
		ft_usleep(table->meal_time, philo);
		return ;
	}
	print(timestamp() - philo->table->start, "is thinking", philo);
	if (table->death_time - table->meal_time <= table->meal_time)
		ft_usleep(table->meal_time, philo);
}

void	*routine(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (1)
	{
		if (is_dead(philo))
			break ;
		eating(philo, philo->table);
		if (philo->nb_meals == philo->table->meals)
			break ;
		if (is_dead(philo))
			break ;
		sleeping(philo, philo->table);
		if (is_dead(philo))
			break ;
		thinking(philo, philo->table);
		if (is_dead(philo))
			break ;
	}
	return (NULL);
}
