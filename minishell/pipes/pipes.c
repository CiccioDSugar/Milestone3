/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:41 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/17 16:17:05 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_exe_syscmd_in_pipe(t_env *env, t_cmd *cmd)
{
	char	*dir;
	int		fd;
	int		saved_stdin;
	char	**matrix_exe;
	int		i;

	i = 0;
	matrix_exe = NULL;
	fd = 0;
	saved_stdin = 0;
	dir = ft_path_finder(env, cmd);
	if (!dir)
		return (env->exit_status = 127, ft_printf(2, "Command not found\n"));
	matrix_exe = ft_mtx_cmd(cmd);
	if (!matrix_exe)
		return (env->exit_status = -1, ft_printf(2, "Malloc Error\n"));
	fd = ft_for_fd(cmd, env, &saved_stdin);
	if (fd == -1 || cmd->open_error)
		return (env->exit_status = -1, ft_free_matrix(matrix_exe),
			free(dir), -1);
	ft_execution_execve(&fd, dir, matrix_exe, env);
	return (0);
}

void	ft_child_routine(int *prev_fd, t_pipe *current,
		t_pipe *head_pipe, t_env *env)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (*prev_fd != -1)
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			return ;
		close(*prev_fd);
	}
	if (current->next || current->one_cmd_flag)
	{
		close(current->pipefd[0]);
		if (dup2(current->pipefd[1], STDOUT_FILENO) == -1)
			return ;
		close (current->pipefd[1]);
	}
	else
	{
		if (current->pipefd[0] != -1)
			close(current->pipefd[0]);
		if (current->pipefd[1] != -1)
			close(current->pipefd[1]);
	}
	ft_exe_pipe_cmd(current, env, current->cmd->tokens, head_pipe);
	return ;
}

void	ft_parent_routine(int *prev_fd, t_pipe *current)
{
	if (*prev_fd != -1)
		close (*prev_fd);
	if (current->next || current->one_cmd_flag)
	{
		close(current->pipefd[1]);
		*prev_fd = current->pipefd[0];
	}
}

static void	ft_pipe_routine(t_pipe *current, t_env *env,
		t_pipe *head_pipe, int *prev_fd)
{
	if (current->next || current->one_cmd_flag)
		pipe(current->pipefd);
	current->pid = fork();
	if (current->pid == 0)
	{
		ft_child_routine(prev_fd, current, head_pipe, env);
		if (*prev_fd != -1)
			close (*prev_fd);
		exit(0);
	}
	else
		ft_parent_routine(prev_fd, current);
}

void	execute_pipe(t_pipe *head_pipe, t_env *env)
{
	t_pipe	*current;
	int		prev_fd;
	int		status;

	prev_fd = -1;
	current = head_pipe;
	status = 0;
	if (!current->next)
		current->one_cmd_flag = true;
	while (current)
	{
		ft_pipe_routine(current, env, head_pipe, &prev_fd);
		current = current->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		get_exit_status(status, env);
	if (prev_fd != -1)
		close (prev_fd);
}
