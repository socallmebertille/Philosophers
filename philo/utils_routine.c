/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:54:40 by saberton          #+#    #+#             */
/*   Updated: 2024/10/30 17:41:41 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	everybody_has_eaten(t_table *table)
{
	t_philo	*philo;
	int		nb;

	if (!table)
		return (1);
	if (table->meals == -1 || table->nb_philo == 1)
		return (0);
	philo = table->first;
	nb = 1;
	while (nb <= table->nb_philo)
	{
		pthread_mutex_lock(&philo->nb_meals_mutex);
		if (philo->nb_meals < table->meals)
		{
			pthread_mutex_unlock(&philo->nb_meals_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->nb_meals_mutex);
		philo = philo->right;
		nb++;
	}
	return (1);
}

int	has_anyone_died(t_table *table)
{
	t_philo	*philo;
	int		nb;

	if (!table)
		return (1);
	philo = table->first;
	nb = 1;
	while (nb <= table->nb_philo)
	{
		pthread_mutex_lock(&philo->status_mutex);
		if (philo->status == DIED)
		{
			pthread_mutex_unlock(&philo->status_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->status_mutex);
		philo = philo->right;
		nb++;
	}
	return (0);
}

int	who_died(t_table *table)
{
	t_philo	*philo;
	int		nb;

	if (!table)
		return (1);
	philo = table->first;
	nb = 1;
	while (nb <= table->nb_philo)
	{
		pthread_mutex_lock(&philo->status_mutex);
		if (philo->status == DIED)
		{
			print(philo->death_time, RED "died" RESET, philo);
			pthread_mutex_unlock(&philo->status_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->status_mutex);
		philo = philo->right;
		nb++;
	}
	return (0);
}

void	print(int timestamp_in_ms, char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%d %d %s\n", timestamp_in_ms, philo->seat, str);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
