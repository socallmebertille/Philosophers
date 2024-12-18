/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:34:17 by saberton          #+#    #+#             */
/*   Updated: 2024/11/05 19:52:47 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	char	*z;

	z = (char *)s;
	while (n-- > 0)
		*z++ = 0;
}

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
		if (nb * sign < -2147483648 || nb * sign > 2147483647)
			return (0);
		i++;
	}
	return (nb * sign);
}

static int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char *str, int nb)
{
	if (str[0] == '-')
		return (printf(RED "Argument %d must be positive. -> " RESET, nb), -1);
	if (!ft_isdigit(str))
		return (printf(RED "Argument %d must be a number. -> " RESET, nb), -1);
	if (nb == 1 && ft_atol(str) > 200)
		return (printf(RED "Argument %d must be less than 200. -> " RESET, nb),
			-1);
	if (nb != 1 && nb != 5 && ft_atol(str) < 60)
		return (printf(RED "Argument %d must be more than 60. -> " RESET, nb),
			-1);
	if (nb == 5 && ft_atol(str) == 0)
		return (-2);
	return (ft_atol(str));
}
