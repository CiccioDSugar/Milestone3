/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:51:11 by fzuccaro          #+#    #+#             */
/*   Updated: 2025/05/20 12:45:59 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;//rende il codice piu leggibile:
typedef struct s_table	t_table;//per far riconoscere t_table al pc

//fork
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;
//philo
typedef struct s_philo
{
	int			id;
	bool		full;
	long		meals_counter;
	long		last_meal_time; //time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
	t_mtx		philo_mutex;
}	t_philo;
//Table
typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_sleep;
	long		time_to_eat;
	long		nbr_limit_meals;// [5] | flag if -1
	long		start_simulation; // time > 0
	bool		end_simulation; //a philo die or all philos are full
	bool		threads_ready;
	long		threads_running;
	t_fork		*forks;//array of struct fork
	t_philo		*philos; //array of struct philo
	t_mtx		table_mutex;//avoid races while reading from table
	t_mtx		write_mutex;
	pthread_t	monitor;
}	t_table;

//mutex
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
}	t_opcode;
//time
typedef enum e_time_code
{
	MILLISECOND,
	MICROSECOND,
}	t_time_code;
//philo states
typedef enum e_status
{
	SLEEPING,
	THINKING,
	EATING,
	DIED,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
}	t_status;
//prototypes
long	ft_atoi(char *nptr);
long	gettime(t_time_code	time_code);
int		error_ex(const char *error);
int		parsing_input(t_table *table, char **av);
int		safe_mutex(t_mtx *mutex, t_opcode opcode);
int		data_init(t_table *table);
void	free_all(t_table *table);
void	dinner_start(t_table *table);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
bool	all_threads_running(t_mtx *mutex, long *thread, long philo_nbr);
bool	philo_died(t_philo *philo);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
void	wait_threads(t_table *table);
void	*dinner_simulation(t_philo *philo);
void	write_status(t_status status, t_philo *philo);
void	precise_usleep(long usec, t_table *table);
void	increase_long(t_mtx *mutex, long *value);
void	*monitor_dinner(t_table *table);
void	*lone_philo(t_philo *philo);
void	clean_all(t_table *table);
void	thinking(t_philo *philo, bool flag);
void	desync(t_philo *philo);
bool	simulation_finished(t_table *table);

#endif
