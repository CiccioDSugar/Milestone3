/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:51:05 by fzuccaro          #+#    #+#             */
/*   Updated: 2025/05/21 17:43:31 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (error_ex("Error with malloc\n"), -1);
	if (ac == 5 || ac == 6)
	{
		if (parsing_input(table, av) == -1)
			return (free(table), -1);
		if (data_init(table) == -1)
			return (-1);
		dinner_start(table);
		clean_all(table);
	}
	else
		return (error_ex("Error: No input\n"), -1);
}
