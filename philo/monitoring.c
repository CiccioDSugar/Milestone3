/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:52:20 by fzuccaro          #+#    #+#             */
/*   Updated: 2025/05/21 11:55:09 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(t_philo *philo)
{
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = ((gettime(MILLISECOND))
			- (get_long(&philo->philo_mutex, &philo->last_meal_time)));
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(&table->philos[i]))
			{
				write_status(DIED, &table->philos[i]);
				set_bool(&table->table_mutex, &table->end_simulation, true);
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
