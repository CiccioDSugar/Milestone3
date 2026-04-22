/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_pt2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:57:37 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/13 11:07:50 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

bool	check_only_env_var(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type != ENV_VAR && tmp->type != SPACES && tmp->type != GARBAGE)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

char	*ft_get_env_value(t_env *env, const char *key)
{
	int		i;
	int		key_len;

	if (!env || !key || !env->env_copy)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env->env_copy[i])
	{
		if (ft_strncmp(env->env_copy[i], key, key_len) == 0
			&& env->env_copy[i][key_len] == '=')
			return (env->env_copy[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

char	*get_var_name(const char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] != '\0' && env_var[i] != '=')
		i++;
	return (ft_substr(env_var, 0, i));
}
