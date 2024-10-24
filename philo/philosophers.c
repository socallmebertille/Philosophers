/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:08:19 by saberton          #+#    #+#             */
/*   Updated: 2024/10/24 14:50:46 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_prog(t_table *table)
{
	t_philo	*cur;
	t_philo	*next;

	if (table->nb_philo <= 0)
		return ;
	if (table->first)
		cur = table->first;
	while (table->nb_philo > 0)
	{
		next = cur->right;
		pthread_mutex_destroy(&cur->fork_mutex);
		pthread_mutex_destroy(&cur->status_mutex);
		free(cur);
		cur = next;
		table->nb_philo -= 1;
	}
	pthread_mutex_destroy(&table->table_mutex);
	if (table)
		free(table);
	table = NULL;
	return ;
}

// static void	print_philo(t_table *table)
// {
// 	t_philo	*cur;
// 	int		i;

// 	cur = table->first;
// 	i = 1;
// 	while (i <= table->nb_philo)
// 	{
// 		printf("[left : %d ]", cur->left->seat);
// 		printf("[seat : %d ", cur->seat);
// 		printf("take fork %d & %d] ", cur->left->fork, cur->fork);
// 		printf("[right] : %d]\n", cur->right->seat);
// 		cur = cur->right;
// 		i++;
// 	}
// }

int	main(int ac, char **av)
{
	t_table	*table;

	// struct timeval    tv;
	// printf("time : %d\n", gettimeofday(&tv, NULL));
	if (ac < 5 || ac > 6)
		return (printf(RED WRONG_ARGS RESET), printf(YELLOW EXEMPLE RESET),
			printf(ORANGE FOR_WHAT RESET), EXIT_FAILURE);
	table = malloc(sizeof(t_table));
	if (!table)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(table),
			EXIT_FAILURE);
	ft_bzero(table, sizeof(t_table));
	if (!init_table(av, table))
		return (EXIT_FAILURE);
	// print_philo(table);
	if (everybody_has_eaten(table))
	{
		printf(GREEN "Everybody has eaten, congrats !!!\n" RESET);
		exit_prog(table);
	}
	return (EXIT_SUCCESS);
}
