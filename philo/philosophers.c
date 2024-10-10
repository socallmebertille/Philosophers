/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:08:19 by saberton          #+#    #+#             */
/*   Updated: 2024/10/09 23:09:11 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_atol(const char *str)
{
	long	nb;
	int		sign;
	int		i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

static int add_philo(t_philo *philo, int num)
{
	t_philo	*new_philo;
	int		i;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (printf(RED "Error malloc.\n" RESET), EXIT_FAILURE);
	i = 1;
	while (i <= num)
	{
		if (i == 1)
			philo->left = new_philo;
		philo->seat = num;
		philo->fork = num;
		// philo->right =
		i++;
	}
	return (1);
}

static int	init_philo(char **av, t_data *data, int nb_philo)
{
	int	num;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (printf(RED "Error malloc.\n" RESET), EXIT_FAILURE);
	data->first = philo;
	data->nb_philo = nb_philo;
	data->nb_fork = nb_philo;
	num = 1;
	while (num <= nb_philo)
	{
		if (!add_philo(data->first, num++))
			return (printf(RED "Error malloc.\n" RESET), EXIT_FAILURE);
		num++;
	}
	data->death_time = ft_atol(av[2]);
	data->meal_time = ft_atol(av[3]);
	data->sleep_time = ft_atol(av[4]);
	if (av[5])
		data->meals = ft_atol(av[2]);
	else
		data->meals = -1;
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 4 || ac > 6)
		return (EXIT_FAILURE);
	printf("Number of philo : [%s].\n", av[1]);
	printf("Philos had [%s] milliseconds before eating.\n", av[2]);
	printf("Philos need to eat during [%s] milliseconds.\n", av[3]);
	printf("Philos sleep at least [%s] milliseconds.\n", av[4]);
	if (ac == 6)
		printf("Number of meals : [%s].\n", av[5]);
	data = malloc(sizeof(t_philo));
	if (!data)
		return (printf(RED "Error malloc.\n" RESET), EXIT_FAILURE);
	if (!init_philo(av, data, ft_atol(av[1])))
		return (free(data), printf(RED "Error malloc.\n" RESET), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
