/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:46:09 by saberton          #+#    #+#             */
/*   Updated: 2024/10/10 18:02:26 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*add_philo(t_data *data, int num)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(data), NULL);
    if (num == data->nb_philo)
    {
        data->first->left = new_philo;
        new_philo->right = data->first;
    }
    new_philo = num;
    new_philo->fork = num;
    // new_philo->right = data->first;
	return (new_philo);
}

static int	init_philo(char **av, t_data *data, int nb_philo)
{
	int		num;
    t_philo	*new_philo;
    t_philo *cur;

    cur = data->first;
	num = 2;
	while (num <= nb_philo)
	{
        new_philo = add_philo(data, num++);
		if (!new_philo)
			return (printf(RED "Error malloc.\n" RESET), exit_prog(data));
        new_philo->left = cur;
        cur = cur->right;
	}
	return (1);
}

int init_data(char **av, t_data *data)
{
    int		num;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(data));
	data->first = philo;
	data->nb_philo = ft_atol(av[1]);
	data->nb_fork = ft_atol(av[1]);
    data->death_time = ft_atol(av[2]);
	data->meal_time = ft_atol(av[3]);
	data->sleep_time = ft_atol(av[4]);
	if (av[5])
		data->meals = ft_atol(av[2]);
	else
		data->meals = -1;
    if (!init_philo(av, data, data->nb_philo))
		return (printf(RED "Init philo failed.\n" RESET), exit_prog(data));
}
