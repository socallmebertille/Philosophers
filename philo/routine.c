/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:40 by saberton          #+#    #+#             */
/*   Updated: 2024/10/22 19:53:45 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo, t_table *table)
{
	// pthread_mutex_lock(&philo->status_mutex);
	philo->status = EATING;
	printf("timestamp_in_ms %d has taken a fork\n", philo->seat);
	if (table->nb_philo == 1)
	{
		printf(RED "timestamp_in_ms %d died\n" RESET, philo->seat);
		// pthread_mutex_unlock(&philo->status_mutex);
		exit_prog(table);
		exit(0);
	}
	printf(BLUE "timestamp_in_ms %d is eating\n" RESET, philo->seat);
	philo->nb_meals += 1;
	// pthread_mutex_unlock(&philo->status_mutex);
}

static void	sleeping(t_philo *philo)
{
	// pthread_mutex_lock(&philo->status_mutex);
	philo->status = SLEEPING;
	if (philo->nb_meals == 0)
	{	
		// pthread_mutex_unlock(&philo->status_mutex);
		return ;
	}
	printf("timestamp_in_ms %d is sleeping\n", philo->seat);
	philo->nb_sleep += 1;
	// pthread_mutex_unlock(&philo->status_mutex);
}

static void	thinking(t_philo *philo)
{
	// pthread_mutex_lock(&philo->status_mutex);
	philo->status = THINKING;
	if (philo->nb_meals == 0)
	{	
		// pthread_mutex_unlock(&philo->status_mutex);
		return ;
	}
	printf("timestamp_in_ms %d is thinking\n", philo->seat);
	philo->nb_think += 1;
	// pthread_mutex_unlock(&philo->status_mutex);
}

static int	everybody_has_eaten(t_table *table)
{
	t_philo	*philo;
	int		nb;

	if (table->meals == -1 || table->nb_philo == 1)
		return (0);
	// pthread_mutex_lock(&table->table_mutex);
	philo = table->first;
	nb = 1;
	while (nb <= table->nb_philo)
	{
		// pthread_mutex_lock(&philo->status_mutex);
		if (philo->nb_meals < table->meals)
		{
			// pthread_mutex_unlock(&philo->status_mutex);
			// pthread_mutex_unlock(&table->table_mutex);
			return (0);
		}
		// pthread_mutex_unlock(&philo->status_mutex);
		philo = philo->right;
		nb++;
	}
	// pthread_mutex_unlock(&table->table_mutex);
	printf(GREEN "Everybody has eaten, congrats !!!\n" RESET);
	exit_prog(table);
	// exit(EXIT_SUCCESS);
	return (1);
}

void	*routine(void *tab)
{
	int		nb;
	t_philo	*philo;
	t_table	*table;
	int turn = 1;

	table = (t_table *)tab;
	while (!everybody_has_eaten(table) && table->nb_philo != 0)
	{
		philo = table->first;
		nb = 1;
		printf(YELLOW "turn n-%d\n" RESET, turn);
		while (nb <= table->nb_philo)
		{
			if (!philo)
				break ;
			// pthread_mutex_lock(&philo->status_mutex);
			if (philo->status == THINKING)
				eating(philo, table);
			else if (philo->status == EATING)
				sleeping(philo);
			else if (philo->status == SLEEPING)
				thinking(philo);
			// pthread_mutex_unlock(&philo->status_mutex);
			philo = philo->right;
			nb++;
		}
		turn++;
	}
	return (table);
}
