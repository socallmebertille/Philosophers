/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:40 by saberton          #+#    #+#             */
/*   Updated: 2024/10/28 19:08:57 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo, t_table *table)
{
	if (philo->status != THINKING)
		return ;
	pthread_mutex_lock(&philo->fork_mutex);
	print(timestamp() - philo->table->start, "has taken a fork", philo);
	if (table->nb_philo == 1)
	{
		philo->status = DIED;
		pthread_mutex_unlock(&philo->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->left->fork_mutex);
	print(timestamp() - philo->table->start, "has taken a fork", philo);
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = EATING;
	pthread_mutex_unlock(&philo->status_mutex);
	print(timestamp() - philo->table->start, BLUE "is eating" RESET, philo);
	pthread_mutex_lock(&philo->nb_meals_mutex);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->nb_meals_mutex);
	philo->last_meal = timestamp() - philo->table->start;
	ft_usleep(table->meal_time, table);
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->left->fork_mutex);
	// if (philo->seat % 2 == 0) {
	// 	pthread_mutex_lock(&philo->left->fork_mutex);
	// 	print(timestamp() - table->start, "has taken a fork", philo);
	// 	pthread_mutex_lock(&philo->fork_mutex);
	// 	print(timestamp() - table->start, "has taken a fork", philo);
	// } else {
	// 	pthread_mutex_lock(&philo->fork_mutex);
	// 	print(timestamp() - table->start, "has taken a fork", philo);
	// 	pthread_mutex_lock(&philo->left->fork_mutex);
	// 	print(timestamp() - table->start, "has taken a fork", philo);
	// }
	// pthread_mutex_lock(&philo->status_mutex);
	// philo->status = EATING;
	// print(timestamp() - table->start, "is eating", philo);
	// pthread_mutex_lock(&philo->nb_meals_mutex);
	// philo->nb_meals++;
	// philo->last_meal = timestamp();
	// pthread_mutex_unlock(&philo->nb_meals_mutex);
	// pthread_mutex_unlock(&philo->status_mutex);
	// ft_usleep(table->meal_time, table);
	// pthread_mutex_unlock(&philo->fork_mutex);
	// pthread_mutex_unlock(&philo->left->fork_mutex);
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
		ft_usleep(table->meal_time, table);
		return ;
	}
	print(timestamp() - philo->table->start, "is sleeping", philo);
	ft_usleep(table->sleep_time, table);
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
		ft_usleep(table->meal_time, table);
		return ;
	}
	print(timestamp() - philo->table->start, "is thinking", philo);
	ft_usleep(table->death_time - (table->meal_time + table->sleep_time),
		table);
}

void	*routine(void *phi)
{
	t_philo	*philo;
	int		turn;

	turn = 1;
	philo = (t_philo *)phi;
	while (!everybody_has_eaten(philo->table))
	{
		if (has_anyone_died(philo->table))
			break ;
		eating(philo, philo->table);
		if (has_anyone_died(philo->table))
			break ;
		sleeping(philo, philo->table);
		if (has_anyone_died(philo->table))
			break ;
		thinking(philo, philo->table);
		if (has_anyone_died(philo->table))
			break ;
		turn++;
	}
	return (NULL);
}
