/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:50:13 by fzuccaro          #+#    #+#             */
/*   Updated: 2025/05/21 17:50:23 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long	ft_atoi(char *nptr)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - 48);
		i++;
	}
	return (result);
}

static int	isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static long	valid_input(char *str)
{
	int		len;
	char	*number;

	len = 0;
	number = NULL;
	while (isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (error_ex("Error: Invalid input\n"), -1);
	if (!ft_isdigit(*str))
		return (error_ex("Error: Invalid input\n"), -1);
	number = str;
	while (ft_isdigit(*str++))
		len++;
	if (len > 10)
		return (error_ex("Error: Invalid input\n"), -1);
	return (ft_atoi(number));
}

// *1e3 for convertion ms in usec for USLEEP
int	parsing_input(t_table *table, char **av)
{
	table->philo_nbr = valid_input(av[1]);
	table->time_to_die = valid_input(av[2]) * 1e3;
	table->time_to_eat = valid_input(av[3]) * 1e3;
	table->time_to_sleep = valid_input(av[4]) * 1e3;
	if ((table->philo_nbr <= 0 || table->philo_nbr > INT_MAX)
		|| (table->time_to_sleep <= 0 || table->time_to_sleep > INT_MAX)
		|| (table->time_to_die <= 0 || table->time_to_die > INT_MAX)
		|| (table->time_to_eat <= 0 || table->time_to_eat > INT_MAX))
		return (error_ex("Error: Invalid input\n"), -1);
	if (av[5])
	{
		table->nbr_limit_meals = valid_input(av[5]);
		if (table->nbr_limit_meals < 0 || table->nbr_limit_meals > INT_MAX)
			return (error_ex("Error: Invalid input\n"), -1);
	}
	else
		table->nbr_limit_meals = -1;
	return (0);
}
