/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:46:09 by saberton          #+#    #+#             */
/*   Updated: 2024/10/24 14:49:34 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*add_philo(t_table *table, int num)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (printf(RED "Error malloc.\n" RESET), NULL);
	ft_bzero(new_philo, sizeof(t_philo));
	new_philo->seat = num;
	new_philo->fork = num;
	new_philo->table = table;
	return (new_philo);
}

static int	status_and_thread(t_table *table, t_philo *philo)
{
	if (table->nb_philo % 2 == 0)
	{
		if (philo->seat % 2 == 0)
			philo->status = SLEEPING;
		else
			philo->status = THINKING;
	}
	else
	{
		if ((philo->seat - 1) % 3 == 0)
			philo->status = THINKING;
		else if ((philo->seat - 2) % 3 == 0)
			philo->status = SLEEPING;
		else if ((philo->seat - 3) % 3 == 0)
			philo->status = EATING;
	}
	if (pthread_create(&philo->thread, NULL, &routine, philo))
		return (printf(RED "Error pthread.\n" RESET), 0);
	pthread_mutex_init(&(philo->status_mutex), NULL);
	pthread_mutex_init(&(philo->fork_mutex), NULL);
	return (1);
}

static int	init_philo(t_table *table, int nb_philo)
{
	int		num;
	t_philo	*new_philo;
	t_philo	*cur;

	num = 1;
	while (num <= nb_philo)
	{
		new_philo = add_philo(table, num);
		if (!new_philo)
			return (printf(RED "Error malloc.\n" RESET), 0);
		if (num == 1)
		{
			table->first = new_philo;
			cur = table->first;
		}
		if (!status_and_thread(table, new_philo))
			return (0);
		new_philo->left = cur;
		cur->right = new_philo;
		cur = cur->right;
		num++;
	}
	table->first->left = new_philo;
	new_philo->right = table->first;
	num = 1;
	cur = table->first;
	while (num < nb_philo)
	{
		if (pthread_join(cur->thread, NULL) && table->nb_philo > 1)
			printf(RED "Error joining thread for %d\n" RESET, cur->seat);
		num++;
	}
	return (1);
}

int	init_table(char **av, t_table *table)
{
	table->nb_philo = ft_atol(av[1]);
	if (table->nb_philo <= 0)
		return (free(table),
			printf(RED "Number of philos must be positive.\n" RESET), 0);
	table->nb_fork = ft_atol(av[1]);
	table->death_time = ft_atol(av[2]);
	table->meal_time = ft_atol(av[3]);
	table->sleep_time = ft_atol(av[4]);
	if (av[5])
		table->meals = ft_atol(av[5]);
	else
		table->meals = -1;
	pthread_mutex_init(&(table->table_mutex), NULL);
	if (!init_philo(table, table->nb_philo))
		return (printf(RED "Init philo failed.\n" RESET), 0);
	return (1);
}
