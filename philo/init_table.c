/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:46:09 by saberton          #+#    #+#             */
/*   Updated: 2024/10/28 18:55:55 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*add_philo(t_table *table, int num)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (printf(RED "Error malloc.\n" RESET), NULL);
	pthread_mutex_init(&(new_philo->fork_mutex), NULL);
	pthread_mutex_init(&(new_philo->nb_meals_mutex), NULL);
	pthread_mutex_init(&(new_philo->status_mutex), NULL);
	pthread_mutex_init(&(new_philo->last_meal_mutex), NULL);
	ft_bzero(new_philo, sizeof(t_philo));
	new_philo->seat = num;
	new_philo->fork = num;
	new_philo->table = table;
	if (num == 1)
		table->first = new_philo;
	return (new_philo);
}

static int	status_philo(t_table *table, t_philo *philo)
{
	if (table->nb_philo % 2 == 0)
	{
		if ((philo->seat - 1) % 2 == 0)
			return (THINKING);
		else if ((philo->seat - 1) % 2 != 0)
			return (SLEEPING);
	}
	else if (table->nb_philo % 2 != 0)
	{
		if ((philo->seat - 1) % 3 == 0)
			return (THINKING);
		else if ((philo->seat - 2) % 3 == 0)
			return (SLEEPING);
		else if ((philo->seat - 3) % 3 == 0)
			return (EATING);
	}
	return (-1);
}

static int	create_thread(t_table *table, int nb_philo)
{
	int		num;
	t_philo	*cur;

	num = 1;
	if (!table->start)
		table->start = timestamp();
	cur = table->first;
	while (num <= nb_philo)
	{
		if (pthread_create(&cur->thread, NULL, &routine, cur))
			return (printf(RED "Error pthread.\n" RESET), 0);
		num++;
		cur = cur->right;
	}
	num = 1;
	cur = table->first;
	while (num <= table->nb_philo && cur)
	{
		pthread_join(cur->thread, NULL);
		cur = cur->right;
		num++;
	}
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
			cur = table->first;
		new_philo->status = status_philo(table, new_philo);
		if ((int)new_philo->status == -1)
			return (0);
		new_philo->left = cur;
		cur->right = new_philo;
		cur = cur->right;
		num++;
	}
	table->first->left = new_philo;
	new_philo->right = table->first;
	create_thread(table, nb_philo);
	return (1);
}

int	init_table(char **av, t_table *table)
{
	table->nb_philo = check_args(av[1], 1);
	if (table->nb_philo == 0)
		return (printf(RED "Number of philos must be positive. -> " RESET), 0);
	table->death_time = check_args(av[2], 2);
	table->meal_time = check_args(av[3], 3);
	table->sleep_time = check_args(av[4], 4);
	if (table->death_time == -1 || table->meal_time == -1
		|| table->sleep_time == -1)
		return (printf(RED "Issue in init.\n" RESET), free(table), exit(0), 0);
	if (av[5])
	{
		table->meals = check_args(av[5], 5);
		if (table->meals == -1)
			return (printf(RED "Issue in init.\n" RESET), free(table), exit(0),
				0);
	}
	else
		table->meals = -1;
	pthread_mutex_init(&(table->table_mutex), NULL);
	pthread_mutex_init(&(table->print_mutex), NULL);
	if (!init_philo(table, table->nb_philo))
		return (printf(RED "Init philo failed. -> " RESET), 0);
	return (1);
}
