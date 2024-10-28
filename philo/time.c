/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:52:50 by saberton          #+#    #+#             */
/*   Updated: 2024/10/28 17:52:23 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_dead(t_table *table, long actual)
{
	t_philo	*philo;
	int		nb;

	if (!table)
		return (0);
	if (table->meals == -1 || table->nb_philo == 1)
		return (0);
	philo = table->first;
	nb = 1;
	while (nb <= table->nb_philo)
	{
		pthread_mutex_lock(&philo->status_mutex);
		if (actual - philo->last_meal > table->death_time && philo->nb_meals)
		{
			philo->status = DIED;
			pthread_mutex_unlock(&philo->status_mutex);
			philo->death_time = timestamp() - table->start;
			return (1);
		}
		pthread_mutex_unlock(&philo->status_mutex);
		philo = philo->right;
		nb++;
	}
	return (0);
}

long long	timestamp(void)
{
	struct	timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = timestamp();
	while ((timestamp() - start) < milliseconds)
	{
		if (is_dead(table, timestamp() - start))
			break ;
		usleep(500);
	}
	return (0);
}
