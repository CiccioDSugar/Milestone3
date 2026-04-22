/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:44:40 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/11/30 18:26:14 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

char	**ft_env_sorted(char **env)
{
	int		i;
	int		swapped;
	char	*swap;

	i = 0;
	swap = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (env[i] && env[i + 1])
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				swap = env[i];
				env[i] = env[i + 1];
				env[i + 1] = swap;
				swapped = 1;
			}
			i++;
		}
	}
	return (env);
}

bool	is_valid_identifier(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (false);
	while (str[i] && str[i] != '=')
		i++;
	if (!ft_isalpha(str[0]) && str[0] != '_'
		&& str[0] != '\'' && str[0] != '\"' && str[0] != ' ')
		return (false);
	while (j < i)
	{
		if (!ft_isalnum(str[j]) && str[j] != '_' && str[j] != '\''
			&& str[j] != '\"' && str[j] != ' ')
			return (false);
		j++;
	}
	return (true);
}

int	ft_find_export_var(t_env *env, char *args)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!args || !env->env_copy)
		return (-1);
	while (args[len] && args[len] != '=')
		len++;
	while (env->env_copy && env->env_copy[i])
	{
		if (!ft_strncmp(env->env_copy[i], args, len)
			&& env->env_copy[i][len] == '=')
			return (i);
		else if (!ft_strncmp(env->env_copy[i], args, len))
			return (i);
		i++;
	}
	return (-1);
}

void	ft_add_var(t_env *env, char **args, int *i)
{
	int		j;
	char	**new_env_copy;

	j = 0;
	new_env_copy = NULL;
	while (env->env_copy[j])
		j++;
	new_env_copy = ft_realloc_mtx(env->env_copy, sizeof(char *) * (j + 2), j);
	if (!new_env_copy)
	{
		ft_printf(2, "Memory allocation failed!\n");
		env->exit_status = 1;
		return ;
	}
	env->env_copy = new_env_copy;
	env->env_copy[j] = ft_strdup(args[(*i)]);
	env->env_copy[j + 1] = NULL;
}

int	is_valid_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg || (!ft_isalpha(arg[0])))
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (0);
		if (!ft_isalnum(arg[i]) && arg[i] != '_'
			&& arg[i] == '/' && arg[i] == ':')
			return (0);
		i++;
	}
	return (1);
}
