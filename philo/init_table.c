/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:46:09 by saberton          #+#    #+#             */
/*   Updated: 2024/10/14 12:09:33 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*add_philo(t_table *table, int num)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(table), NULL);
	new_philo->seat = num;
	new_philo->fork = num;
	return (new_philo);
}

static int	init_philo(t_table *table, int nb_philo)
{
	int		num;
	t_philo	*new_philo;
	t_philo	*cur;

	cur = table->first;
	num = 2;
	while (num <= nb_philo)
	{
		new_philo = add_philo(table, num);
		if (!new_philo)
			return (printf(RED "Error malloc.\n" RESET), exit_prog(table));
		if ((new_philo->seat - 1) % 3 == 0)
			new_philo->status = THINKING;
		else if ((new_philo->seat - 2) % 3 == 0)
			new_philo->status = EATING;
		else if ((new_philo->seat - 3) % 3 == 0)
			new_philo->status = SLEEPING;
		new_philo->left = cur;
		cur->right = new_philo;
		cur = cur->right;
		num++;
	}
	table->first->left = new_philo;
	new_philo->right = table->first;
	return (1);
}

int	init_table(char **av, t_table *table)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(table));
	table->first = philo;
	table->first->seat = 1;
	table->first->fork = 1;
	table->first->status = THINKING;
	table->nb_philo = ft_atol(av[1]);
	table->nb_fork = ft_atol(av[1]);
	table->death_time = ft_atol(av[2]);
	table->meal_time = ft_atol(av[3]);
	table->sleep_time = ft_atol(av[4]);
	if (av[5])
		table->meals = ft_atol(av[5]);
	else
		table->meals = -1;
	if (!init_philo(table, table->nb_philo))
		return (printf(RED "Init philo failed.\n" RESET), exit_prog(table));
	return (1);
}