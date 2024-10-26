/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:40 by saberton          #+#    #+#             */
/*   Updated: 2024/10/26 23:03:11 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&philo->status_mutex);
	pthread_mutex_lock(&philo->fork_mutex);
	// if (philo->nb_meals == 0)
	// 	philo->start = timestamp();
	print(timestamp() - philo->table->start, "has taken a fork", philo);
	if (table->nb_philo == 1)
	{
		philo->status = DIED;
		pthread_mutex_unlock(&philo->status_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
		return ;
	}
	// pthread_mutex_lock(&philo->left->fork_mutex);
	philo->status = EATING;
	// printf("go eat with fork %d & %d\n", philo->left->fork, philo->fork);
	print(timestamp() - philo->table->start, BLUE "is eating" RESET, philo);
	pthread_mutex_lock(&philo->nb_meals_mutex);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->status_mutex);
	pthread_mutex_unlock(&philo->nb_meals_mutex);
	ft_usleep(table->meal_time, table);
	philo->last_meal = timestamp() - philo->table->start + philo->nb_meals * table->meal_time;
	// print(philo->last_meal, "a eu dernier repas", philo);
	pthread_mutex_unlock(&philo->fork_mutex);
	// pthread_mutex_unlock(&philo->left->fork_mutex);
}

static void	sleeping(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = SLEEPING;
	if (philo->nb_meals == 0)
	{
		ft_usleep(table->sleep_time, table);
		pthread_mutex_unlock(&philo->status_mutex);
		return ;
	}
	print(timestamp() - philo->table->start, "is sleeping", philo);
	ft_usleep(table->sleep_time, table);
	philo->nb_sleep += 1;
	pthread_mutex_unlock(&philo->status_mutex);
}

static void	thinking(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&philo->status_mutex);
	philo->status = THINKING;
	if (philo->nb_meals == 0)
	{
		ft_usleep(table->meal_time, table);
		pthread_mutex_unlock(&philo->status_mutex);
		return ;
	}
	print(timestamp() - philo->table->start, "is thinking", philo);
	ft_usleep(table->meal_time - table->sleep_time, table);
	philo->nb_think += 1;
	pthread_mutex_unlock(&philo->status_mutex);
}

void	*routine(void *phi)
{
	t_philo		*philo;
	int			turn;

	turn = 1;
	philo = (t_philo *)phi;
	while (!everybody_has_eaten(philo->table))
	{
		// printf(YELLOW "turn n-%d\n" RESET, turn);
		if (turn == 1)
			philo->table->start = timestamp();
		if (philo->status == THINKING)
			eating(philo, philo->table);
		if (has_anyone_died(philo->table))
			break ;
		if (philo->status == EATING)
			sleeping(philo, philo->table);
		if (has_anyone_died(philo->table))
			break ;
		if (philo->status == SLEEPING)
			thinking(philo, philo->table);
		if (has_anyone_died(philo->table))
			break ;
		turn++;
	}
	return (NULL);
}
