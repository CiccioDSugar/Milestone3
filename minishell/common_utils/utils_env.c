/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:06:40 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/13 11:14:03 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

bool	ft_find_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void	ft_expand(int *i, char *str, t_env *env, char **result)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*tmp;

	(*i)++;
	start = *i;
	var_name = NULL;
	var_value = NULL;
	if (ft_isdigit(str[(*i)]))
		(*i)++;
	else
	{
		while (str[(*i)] && (ft_isalnum(str[(*i)]) || str[(*i)] == '_'))
			(*i)++;
	}
	var_name = ft_substr(str, start, *i - start);
	var_value = ft_get_env_value(env, var_name);
	if (var_value)
	{
		tmp = ft_strjoin(*result, var_value);
		free (*result);
		*result = tmp;
	}
	free(var_name);
}

void	ft_merge_str(int *i, char *str, char **result)
{
	int		start;
	char	*tmp;
	char	*literal;

	start = *i;
	tmp = NULL;
	literal = NULL;
	while (str[(*i)] && str[(*i)] != '$')
		(*i)++;
	literal = ft_substr(str, start, *i - start);
	tmp = ft_strjoin(*result, literal);
	free(*result);
	*result = tmp;
	free(literal);
}

char	*ft_expand_envvar(char *str, t_env *env)
{
	int		i;
	int		start;
	char	*result;
	char	*tmp;
	char	*literal;

	i = 0;
	start = 0;
	tmp = NULL;
	literal = NULL;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			ft_expand(&i, str, env, &result);
		else
			ft_merge_str(&i, str, &result);
	}
	return (result);
}
