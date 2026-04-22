/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:35:08 by fzuccaro          #+#    #+#             */
/*   Updated: 2025/05/21 17:44:37 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_fork(t_philo *philo, t_fork *fork, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &fork[(position + 1) % philo_nbr];
	philo->second_fork = &fork[position];
	if ((philo->id % 2) == 0)
	{
		philo->first_fork = &fork[position];
		philo->second_fork = &fork[(position + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	philo = NULL;
	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex(&philo->philo_mutex, INIT);
		assign_fork(philo, table->forks, i);
		i++;
	}
}

int	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (error_ex("Error with malloc\n"));
	table->end_simulation = false;
	table->threads_ready = false;
	table->threads_running = 0;
	safe_mutex(&table->table_mutex, INIT);
	safe_mutex(&table->write_mutex, INIT);
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
		return (error_ex("Error with malloc\n"));
	while (i < table->philo_nbr)
	{
		if (safe_mutex(&table->forks[i].fork, INIT) == -1)
			return (-1);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
	return (0);
}
