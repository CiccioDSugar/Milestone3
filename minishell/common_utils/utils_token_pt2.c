/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_pt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:04:10 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/13 11:48:49 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

bool	is_redir(t_token *tokens)
{
	if (tokens->type == REDIR_IN
		|| tokens->type == REDIR_OUT || tokens->type == REDIR_APPEND)
		return (true);
	return (false);
}

bool	is_argument(t_token *tokens)
{
	if (tokens->type == ARGUMENT || tokens->type == ENV_VAR
		|| tokens->type == QUOTE || tokens->type == EXIT_STATUS)
		return (true);
	return (false);
}

bool	is_space(t_token *tokens)
{
	if (tokens->type == SPACES || tokens->type == GARBAGE)
		return (true);
	return (false);
}

bool	is_n_sequence(char *str)
{
	int	i;

	i = 2;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	ft_assign_spaces(t_token *prev, t_token *tokens, int *between_arg)
{
	if (prev && prev->type == ARGUMENT && is_n_sequence(prev->value))
		tokens->type = GARBAGE;
	else if (prev && ((prev->type == ARGUMENT || prev->type == ENV_VAR
				|| prev->type == QUOTE)
			&& tokens->next && (tokens->next->type == ARGUMENT
				|| tokens->next->type == ENV_VAR
				|| tokens->next->type == QUOTE)))
	{
		if (!*between_arg)
		{
			tokens->type = SPACES;
			*between_arg = 1;
		}
		else
			tokens->type = GARBAGE;
	}
	else
		tokens->type = GARBAGE;
}
