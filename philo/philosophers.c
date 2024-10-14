/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:08:19 by saberton          #+#    #+#             */
/*   Updated: 2024/10/14 17:04:10 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_prog(t_table *table)
{
	t_philo	*tmp;
	t_philo	*next;

	if (table->first)
		tmp = table->first;
	while (table->nb_philo-- > 0)
	{
		next = tmp->right;
		free(tmp);
		tmp = next;
	}
	if (table)
		free(table);
	table = NULL;
	return (EXIT_FAILURE);
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

	if (ac < 5 || ac > 6)
		return (printf(RED WRONG_ARGS RESET), printf(YELLOW EXEMPLE RESET),
			printf(ORANGE FOR_WHAT RESET), EXIT_FAILURE);
	table = malloc(sizeof(t_table));
	if (!table)
		return (printf(RED "Error malloc.\n" RESET), exit_prog(table));
	ft_bzero(table, sizeof(t_table));
	if (!init_table(av, table))
		return (printf(RED "Error malloc.\n" RESET), exit_prog(table));
	// print_philo(table);
	routine(table);
	exit_prog(table);
	return (EXIT_SUCCESS);
}
