/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:08:19 by saberton          #+#    #+#             */
/*   Updated: 2024/10/11 16:30:30 by saberton         ###   ########.fr       */
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
	return (EXIT_FAILURE);
}

static void	print_philo(t_data *data)
{
	t_philo	*cur;
	int		i;

	cur = data->first;
	i = 1;
	while (i <= data->nb_philo)
	{
		printf("[left : %d ]", cur->left->seat);
		printf("[seat : %d ]", cur->seat);
		printf("[right] : %d]\n", cur->right->seat);
		cur = cur->right;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 4 || ac > 6)
		return (printf(RED WRONG_ARGS RESET), printf(YELLOW EXEMPLE RESET),
			printf(ORANGE FOR_WHAT RESET), EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(data));
	ft_bzero(data, sizeof(t_data));
	if (!init_data(av, data))
		return (printf(RED "Error malloc.\n" RESET), exit_prog(data));
	print_philo(data);
	return (EXIT_SUCCESS);
}
