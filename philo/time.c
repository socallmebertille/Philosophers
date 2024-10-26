/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:52:50 by saberton          #+#    #+#             */
/*   Updated: 2024/10/26 22:34:27 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_dead(t_table *table)
{
	(void)table;
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
		usleep(500);
		if (is_dead(table))
			break ;
	}
	return (0);
}
