/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:40 by saberton          #+#    #+#             */
/*   Updated: 2024/10/14 17:04:40 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo)
{
	philo->status = EATING;
	printf("timestamp_in_ms %d has taken a fork\n", philo->seat);
	printf(BLUE "timestamp_in_ms %d is eating\n" RESET, philo->seat);
	philo->nb_meals += 1;
}

static void	sleeping(t_philo *philo)
{
	philo->status = SLEEPING;
	if (philo->nb_meals == 0)
		return ;
	printf("timestamp_in_ms %d is sleeping\n", philo->seat);
	philo->nb_sleep += 1;
}

static void	thinking(t_philo *philo)
{
	philo->status = THINKING;
	if (philo->nb_meals == 0)
		return ;
	printf("timestamp_in_ms %d is thinking\n", philo->seat);
	philo->nb_think += 1;
}

static int	everybody_has_eaten(t_table *table)
{
	t_philo	*philo;
	int		nb;

	if (table->meals == -1)
		return (0);
	philo = table->first;
	nb = 1;
	while (nb <= table->nb_philo)
	{
		if (philo->nb_meals < table->meals)
			return (0);
		philo = philo->right;
		nb++;
	}
	printf("Everybody has eaten, congrats !!!\n");
	return (1);
}

void	*routine(t_table *table)
{
	int		nb;
	t_philo	*philo;

	while (!everybody_has_eaten(table))
	{
		philo = table->first;
		nb = philo->seat;
		while (nb <= table->nb_philo)
		{
			if (philo->status == THINKING)
				eating(philo);
			else if (philo->status == EATING)
				sleeping(philo);
			else if (philo->status == SLEEPING)
				thinking(philo);
			philo = philo->right;
			nb++;
		}
	}
	return (table);
}
