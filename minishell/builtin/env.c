/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:06:23 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:17 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '=')
		i++;
	if (str[i + 1] != '\0')
		return (1);
	return (0);
}

static void	print_args(t_env *env, int *i, int fd)
{
	while (env->env_copy[(*i)])
	{
		if (strchr(env->env_copy[(*i)], '=')
			&& check_value(env->env_copy[(*i)]))
			ft_printf(fd, "%s\n", env->env_copy[(*i)]);
		(*i)++;
	}
	env->exit_status = 0;
}

static void	ft_env_error(t_env *env, t_cmd *cmd, int *i, int *error_flag)
{
	if (cmd->args[*i])
	{
		ft_printf(2, "env: %s not a valid identifier\n", cmd->args[*i]);
		env->exit_status = 1;
		*error_flag = 1;
	}
	else if (env->path_deleted)
	{
		ft_printf(2, "%s", "minishell: env: No such file or directory\n");
		*error_flag = 1;
	}
}

void	ft_env(t_cmd *cmd, t_env *env, t_pipe *head)
{
	int	i;
	int	fd;
	int	saved_stdin;
	int	error_flag;

	i = 0;
	error_flag = 0;
	saved_stdin = 0;
	fd = ft_for_fd(cmd, env, &saved_stdin);
	if (fd == -1 || cmd->open_error)
		return ;
	ft_env_error(env, cmd, &i, &error_flag);
	if (!error_flag)
		print_args(env, &i, fd);
	if (fd != 1)
		close(fd);
	if (cmd->input)
		restore_sdin(&saved_stdin);
	if (cmd->pipe_flag)
		free_all_pipe(head, env);
	return ;
}
