/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:08:19 by saberton          #+#    #+#             */
/*   Updated: 2024/11/02 20:35:47 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	everybody_has_eaten(t_table *table)
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

static void	check_death(t_table *table)
{
	while (1)
	{
		if (checkvarisdead(table))
			break ;
		if (everybody_has_eaten(table))
			break ;
	}
}

static void	loop_free(t_table *table)
{
	int		num;
	t_philo	*cur;
	t_philo	*next;

	num = 1;
	cur = table->first;
	while (num <= table->nb_philo)
	{
		next = cur->right;
		pthread_mutex_destroy(&cur->fork_mutex);
		pthread_mutex_destroy(&cur->nb_meals_mutex);
		pthread_mutex_destroy(&cur->status_mutex);
		free(cur);
		cur = next;
		num++;
	}
	return ;
}

void	exit_prog(t_table *table)
{
	if (table->nb_philo <= 0)
		return (free(table));
	check_death(table);
	pthread_mutex_lock(&table->table_mutex);
	loop_free(table);
	pthread_mutex_unlock(&table->table_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	if (table)
		free(table);
	table = NULL;
	return ;
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac < 5 || ac > 6)
		return (printf(RED WRONG_ARGS RESET), printf(YELLOW EXEMPLE RESET),
			printf(ORANGE FOR_WHAT RESET), EXIT_FAILURE);
	table = malloc(sizeof(t_table));
	if (!table)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(table),
			EXIT_FAILURE);
	ft_bzero(table, sizeof(t_table));
	if (!init_table(av, table))
		return (printf(RED "Issue in init.\n" RESET), exit_prog(table),
			EXIT_FAILURE);
	exit_prog(table);
	return (EXIT_SUCCESS);
}
