/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sintax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:38:25 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:51:18 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdbool.h>

bool	check_redir(t_token *tmp)
{
	if (tmp->next)
	{
		tmp = tmp->next;
		while (tmp->next && (tmp->type == SPACES || tmp->type == GARBAGE))
			tmp = tmp->next;
		if (tmp->type != FILE_ || tmp->value[0] == '>' || tmp->value[0] == '<')
		{
			error_ex("minishell:syntax error near unexpected token newline\n");
			return (true);
		}
	}
	else if (!tmp->next)
	{
		error_ex("minishell:syntax error near unexpected token newline\n");
		return (true);
	}
	return (false);
}

bool	check_heredoc(t_token *tmp)
{
	if (tmp->next)
	{
		tmp = tmp->next;
		while (tmp->next && (tmp->type == SPACES || tmp->type == GARBAGE))
			tmp = tmp->next;
		if (tmp->type != DELIMITER
			|| (!ft_isalnum(tmp->value[0]) && ft_strncmp("_", tmp->value, 1)))
		{
			error_ex("minishell:syntax error near unexpected token newline\n");
			return (true);
		}
	}
	else if (!tmp->next)
	{
		error_ex("minishell:syntax error near unexpected token newline\n");
		return (true);
	}
	return (false);
}

bool	check_pipe(t_token *tmp)
{
	if (tmp->next)
	{
		tmp = tmp->next;
		while (tmp->next && (tmp->type == SPACES || tmp->type == GARBAGE))
			tmp = tmp->next;
		if (tmp->type != COMMAND && (!is_redir(tmp)) && tmp->type != HEREDOC)
		{
			error_ex("minishell: syntax error near unexpected token `|'\n");
			return (true);
		}
	}
	else if (!tmp->next)
	{
		error_ex("minishell: syntax error near unexpected token `|'\n");
		return (true);
	}
	return (false);
}

bool	check_command(t_token *tmp)
{
	t_token	*prev;

	prev = tmp;
	if (tmp->next)
	{
		tmp = tmp->next;
		if (!is_space(tmp))
		{
			ft_printf(2, "minishell: command not found %s%s\n",
				prev->value, tmp->value);
			return (true);
		}
		return (false);
	}
	return (false);
}

bool	check_only_spaces(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type != SPACES && tmp->type != GARBAGE)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
