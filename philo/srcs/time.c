/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:52:50 by saberton          #+#    #+#             */
/*   Updated: 2024/11/03 06:03:00 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (checkvarisdead(table))
		return (1);
	if (timestamp() - table->start - philo->last_meal > table->death_time
		&& philo->status != DIED)
	{
		pthread_mutex_lock(&philo->status_mutex);
		philo->status = DIED;
		pthread_mutex_unlock(&philo->status_mutex);
		pthread_mutex_lock(&table->table_mutex);
		philo->table->isdead = 1;
		pthread_mutex_unlock(&table->table_mutex);
		return (1);
	}
	return (0);
}

int	checkvarisdead(t_table *table)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->table_mutex);
	ret = table->isdead;
	pthread_mutex_unlock(&table->table_mutex);
	return (ret);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = timestamp();
	while ((timestamp() - start) < milliseconds)
	{
		if (is_dead(philo))
			break ;
		usleep(500);
	}
	return ;
}

void	print(int timestamp_in_ms, char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%d %d %s\n", timestamp_in_ms, philo->seat, str);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
