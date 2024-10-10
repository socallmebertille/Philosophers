/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:08:19 by saberton          #+#    #+#             */
/*   Updated: 2024/10/10 17:54:45 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_prog(t_data *data)
{
	t_philo	*tmp;
	t_philo	*next;

	if (data->first)
		tmp = data->first;
	while (data->nb_philo-- > 0)
	{
		next = tmp->right;
		free(tmp);
		tmp = next;
	}
	if (data)
		free(data);
	data = NULL;
	retun(EXIT_FAILURE);
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
		return (printf(RED "Error malloc.\n" RESET), exit_prog(data));
	ft_bzero(data, sizeof(t_data));
	if (!init_data(av, data))
		return (printf(RED "Error malloc.\n" RESET), exit_prog(data));
	return (EXIT_SUCCESS);
}
