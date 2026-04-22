/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:49:46 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:14:22 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>
#include <string.h>

static void	ft_for_delete(t_env *env, char *arg, char **new_env)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	key = NULL;
	while (env->env_copy[i])
	{
		key = get_var_name(env->env_copy[i]);
		if (!key || ft_strcmp(key, arg) != 0)
		{
			new_env[j] = ft_strdup(env->env_copy[i]);
			if (!new_env[j])
			{
				ft_free_matrix(new_env);
				free(key);
				return ;
			}
			j++;
		}
		free(key);
		i++;
	}
	new_env[j] = NULL;
}

void	ft_delete_var(t_env *env, int index, char *arg)
{
	int		len;
	int		i;
	char	**new_env;

	len = 0;
	i = 0;
	new_env = NULL;
	while (env->env_copy[i])
	{
		if (i != index)
			len++;
		i++;
	}
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return ;
	ft_for_delete(env, arg, new_env);
	ft_free_matrix(env->env_copy);
	env->env_copy = new_env;
}

int	ft_find_unset_var(t_env *env, char *args)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while (env->env_copy[i])
	{
		key = get_var_name(env->env_copy[i]);
		if (key && ft_strcmp(key, args) == 0)
		{
			if (!ft_strcmp(args, "PATH"))
				env->path_deleted = true;
			free(key);
			return (i);
		}
		free(key);
		i++;
	}
	return (-1);
}

bool	exe_unset(t_cmd *cmd, t_env *env, int *i, int index)
{
	if (is_valid_unset_arg(cmd->args[(*i)]))
	{
		index = ft_find_unset_var(env, cmd->args[(*i)]);
		if (index >= 0)
			ft_delete_var(env, index, cmd->args[(*i)]);
	}
	else
	{
		ft_printf(2, "unset: `%s': not a valid identifier\n", cmd->args[(*i)]);
		env->exit_status = 1;
		return (false);
	}
	(*i)++;
	return (true);
}

void	ft_unset(t_cmd *cmd, t_env *env, t_pipe *head)
{
	int	index;
	int	i;
	int	fd;
	int	saved_stdin;

	i = 0;
	index = -1;
	saved_stdin = 0;
	fd = ft_for_fd(cmd, env, &saved_stdin);
	if (fd == -1 || cmd->open_error)
		return ;
	while (cmd->args[i])
	{
		if (!exe_unset(cmd, env, &i, index))
			return ;
	}
	if (cmd->input)
		restore_sdin(&saved_stdin);
	if (fd != 1)
		close (fd);
	env->exit_status = 0;
	if (cmd->pipe_flag)
		free_all_pipe(head, env);
}
