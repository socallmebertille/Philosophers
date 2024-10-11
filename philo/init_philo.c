/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:46:09 by saberton          #+#    #+#             */
/*   Updated: 2024/10/11 14:52:00 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*add_philo(t_data *data, int num)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(data), NULL);
	new_philo->seat = num;
	new_philo->fork = num;
	return (new_philo);
}

static int	init_philo(t_data *data, int nb_philo)
{
	int		num;
	t_philo	*new_philo;
	t_philo	*cur;

	cur = data->first;
	num = 2;
	while (num <= nb_philo)
	{
		new_philo = add_philo(data, num);
		if (!new_philo)
			return (printf(RED "Error malloc.\n" RESET), exit_prog(data));
		new_philo->left = cur;
		cur->right = new_philo;
		cur = cur->right;
		num++;
	}
	data->first->left = new_philo;
	new_philo->right = data->first;
	return (1);
}

int	init_data(char **av, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(data));
	data->first = philo;
	data->first->seat = 1;
	data->first->fork = 1;
	data->nb_philo = ft_atol(av[1]);
	data->nb_fork = ft_atol(av[1]);
	data->death_time = ft_atol(av[2]);
	data->meal_time = ft_atol(av[3]);
	data->sleep_time = ft_atol(av[4]);
	if (av[5])
		data->meals = ft_atol(av[2]);
	else
		data->meals = -1;
	if (!init_philo(data, data->nb_philo))
		return (printf(RED "Init philo failed.\n" RESET), exit_prog(data));
	return (1);
}
