/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:05:25 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/17 16:10:49 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system_commands.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_path_finder(t_env *env, t_cmd *cmd)
{
	char	*path;
	char	**dir_matrix;
	char	*cmd_path;
	int		i;

	i = 0;
	if (cmd->cmd[0] == '/' || (cmd->cmd[0] == '.' && cmd->cmd[1] == '/'))
	{
		if (access(cmd->cmd, X_OK) == 0)
			return (ft_strdup(cmd->cmd));
		return (NULL);
	}
	path = ft_strdup(ft_get_env_value(env, "PATH"));
	dir_matrix = ft_split(path, ':');
	while (dir_matrix[i++] != NULL)
	{
		cmd_path = ft_strjoin_three(dir_matrix[i], "/", cmd->cmd);
		if (cmd_path && access(cmd_path, X_OK) == 0)
			return (ft_free_matrix(dir_matrix), free(path), cmd_path);
		else
			free(cmd_path);
	}
	return (ft_free_matrix(dir_matrix), free(path), NULL);
}

char	**ft_mtx_cmd(t_cmd *cmd)
{
	char	**matrix_exe;
	int		i;
	int		j;

	i = 0;
	j = 1;
	matrix_exe = malloc(sizeof(char *) * (ft_matrix_len(cmd->args) + 2));
	if (!matrix_exe)
		return (ft_printf(2, "Malloc Error\n"), NULL);
	matrix_exe[0] = ft_strdup(cmd->cmd);
	while (cmd->args[i])
	{
		matrix_exe[j] = ft_strdup(cmd->args[i]);
		i++;
		j++;
	}
	matrix_exe[j] = NULL;
	return (matrix_exe);
}

void	ft_execution(char **dir, char **matrix_exe, t_env *env)
{
	if (dir && execve(*dir, matrix_exe, env->env_copy) == -1)
	{
		perror("execve");
		ft_free_matrix(matrix_exe);
		free(dir);
		env->exit_status = 126;
	}
}

int	ft_child(t_cmd *cmd, t_env *env, char **dir)
{
	char	**matrix_exe;
	int		saved_stdin;
	int		fd;

	saved_stdin = 0;
	matrix_exe = ft_mtx_cmd(cmd);
	fd = 1;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (!matrix_exe)
		return (-1);
	fd = ft_for_fd(cmd, env, &saved_stdin);
	if (fd == -1)
		return (free(*dir),
			ft_free_matrix(matrix_exe), free_all(cmd, env), -1);
	if (fd != 1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
		close (fd);
	}
	ft_execution(dir, matrix_exe, env);
	return (0);
}

//signal(SIGINT, SIG_IGN); linea 118 eliminato questo segnale
int	ft_exe_syscmd(t_env *env, t_cmd *cmd)
{
	pid_t	pid;
	char	*dir;
	int		i;
	int		status;

	if (cmd->open_error)
		return (-1);
	i = 0;
	dir = ft_path_finder(env, cmd);
	if (env->path_deleted || !dir)
		return (env->exit_status = 127, ft_printf(2,
				"minishell: command not found: %s\n", cmd->cmd));
	pid = fork();
	if (pid == 0)
	{
		ft_child(cmd, env, &dir);
		exit(126);
	}
	else
	{
		waitpid(pid, &status, 0);
		get_exit_status(status, env);
	}
	return (free(dir), 0);
}

/*da cosi:
int	ft_exe_syscmd(t_env *env, t_cmd *cmd)
{
	pid_t	pid;
	char	*dir;
	int		i;
	int		status;

	if (cmd->open_error)
		return (-1);
	i = 0;
	if (env->path_deleted)
		return (env->exit_status = 127, ft_printf(2,
				"minishell: command not found: %s\n", cmd->cmd));
	dir = ft_path_finder(env, cmd);
	if (!dir)
		return (env->exit_status = 127, ft_printf(2,
			"minishell: command not found: %s\n", cmd->cmd));
	pid = fork();
	if (pid == 0)
	{
		ft_child(cmd, env, &dir);
		exit(126);
	}
	else
	{
		waitpid(pid, &status, 0);
		get_exit_status(status, env);
	}
	return (free(dir), 0);
}
	a cosi:
	int	ft_exe_syscmd(t_env *env, t_cmd *cmd)
{
	pid_t	pid;
	char	*dir;
	int		i;
	int		status;

	if (cmd->open_error)
		return (-1);
	i = 0;
	dir = ft_path_finder(env, cmd);
	if (env->path_deleted || !dir)
		return (env->exit_status = 127, ft_printf(2,
				"minishell: command not found: %s\n", cmd->cmd));
	pid = fork();
	if (pid == 0)
	{
		ft_child(cmd, env, &dir);
		exit(126);
	}
	else
	{
		waitpid(pid, &status, 0);
		get_exit_status(status, env);
	}
	return (free(dir), 0);
}*/
