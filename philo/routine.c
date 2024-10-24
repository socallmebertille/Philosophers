/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:40 by saberton          #+#    #+#             */
/*   Updated: 2024/10/24 17:29:36 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (philo->left && philo->left->fork != philo->fork)
		pthread_mutex_lock(&philo->left->fork_mutex);
	printf("timestamp_in_ms %d has taken a fork\n", philo->seat);
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = EATING;
	if (philo->left->fork == philo->fork)
	{
		printf(RED "timestamp_in_ms %d died\n" RESET, philo->seat);
		pthread_mutex_unlock(&philo->status_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		if (philo->left && philo->left->fork != philo->fork)
			pthread_mutex_unlock(&philo->left->fork_mutex);
		pthread_detach(philo->thread);
		return ;
	}
	printf(BLUE "timestamp_in_ms %d is eating\n" RESET, philo->seat);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->status_mutex);
	usleep(table->meal_time * 1000);
	pthread_mutex_unlock(&philo->fork_mutex);
	if (philo->left && philo->left->fork != philo->fork)
		pthread_mutex_unlock(&philo->left->fork_mutex);
	pthread_detach(philo->thread);
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
	printf("timestamp_in_ms %d is sleeping\n", philo->seat);
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
	printf("timestamp_in_ms %d is thinking\n", philo->seat);
	philo->nb_think += 1;
	pthread_mutex_unlock(&philo->status_mutex);
}
// usleep(table->think_time * 1000); // Temps de réflexion

int	everybody_has_eaten(t_table *table)
{
	t_philo	*philo;
	int		nb;

	if (!table)
		return (1);
	if (table->meals == -1 || table->nb_philo == 1)
		return (0);
	pthread_mutex_lock(&table->table_mutex);
	philo = table->first;
	nb = 1;
	while (nb <= table->nb_philo)
	{
		pthread_mutex_lock(&philo->status_mutex);
		if (philo->nb_meals < table->meals)
		{
			pthread_mutex_unlock(&philo->status_mutex);
			pthread_mutex_unlock(&table->table_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->status_mutex);
		philo = philo->right;
		nb++;
	}
	pthread_mutex_unlock(&table->table_mutex); 
	return (1);
}

void	*routine(void *phi)
{
	t_philo	*philo;
	int		turn;

	turn = 1;
	philo = (t_philo *)phi;
	while (!everybody_has_eaten(philo->table))
	{
		if (!philo->table->nb_philo)
			return (NULL);
		if (!philo->left)
			return (NULL);
		printf(YELLOW "turn n-%d\n" RESET, turn);
		eating(philo, philo->table);
		sleeping(philo, philo->table);
		thinking(philo);
		turn++;
	}
	return (NULL);
}
