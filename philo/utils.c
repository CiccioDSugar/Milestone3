/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:51:14 by fzuccaro          #+#    #+#             */
/*   Updated: 2025/05/20 12:43:01 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	error_ex(const char *error)
{
	printf("%s", error);
	return (-1);
}

void	write_status(t_status status, t_philo *philo)
{
	if (philo->full)
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf("%lu %d has taken a fork\n", (gettime(MILLISECOND)
				- philo->table->start_simulation), philo->id + 1);
	else if (status == EATING && !simulation_finished(philo->table))
		printf("%lu %d is eating\n", (gettime(MILLISECOND)
				- philo->table->start_simulation), philo->id + 1);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf("%lu %d is thinking\n", (gettime(MILLISECOND)
				- philo->table->start_simulation), philo->id + 1);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf("%lu %d is sleeping\n", (gettime(MILLISECOND)
				- philo->table->start_simulation), philo->id + 1);
	else if (status == DIED && !simulation_finished(philo->table))
		printf("%lu %d is died\n", (gettime(MILLISECOND)
				- philo->table->start_simulation), philo->id + 1);
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 10e3)
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

void	clean_all(t_table *table)
{
	int		i;
	t_philo	*philo;

	if (!table || !table->philos)
		return ;
	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
		i++;
	}
	safe_mutex(&table->table_mutex, DESTROY);
	safe_mutex(&table->write_mutex, DESTROY);
	free(table->philos);
	free(table->forks);
	free(table);
}
