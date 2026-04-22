/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fuction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:20:39 by fzuccaro          #+#    #+#             */
/*   Updated: 2025/05/21 17:43:19 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/types.h>

static int	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (0);
	if ((status == EINVAL) && ((opcode == LOCK) || (opcode == UNLOCK)))
		return (error_ex("The value specified by mutex is invalid\n"), -1);
	else if (status == EINVAL && opcode == INIT)
		return (error_ex("The value specified by attr is invalid\n"), -1);
	else if (status == EDEADLK)
		return (error_ex("DL if threads blocked waiting for mutex\n"), -1);
	else if (status == EPERM)
		return (error_ex("The current thread doesn't hold a mutex lock\n"), -1);
	else if (status == ENOMEM)
		return (error_ex("Process cannot allocate memory for a mutex\n"), -1);
	else if (status == EBUSY)
		return (error_ex("Mutex is locked"), -1);
	return (0);
}

int	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (!mutex)
		return (error_ex("ERRORE MUTEX\n"), -1);
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		return (0);
	return (0);
}
