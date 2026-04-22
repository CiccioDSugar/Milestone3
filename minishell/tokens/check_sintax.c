/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sintax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:54:34 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/15 17:16:26 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

bool	ft_sintax_errors(t_token *tmp)
{
	if (is_redir(tmp))
	{
		if (check_redir(tmp) == true)
			return (true);
	}
	else if (tmp->type == HEREDOC)
	{
		if (check_heredoc(tmp) == true)
			return (true);
	}
	else if (tmp->type == PIPE)
	{
		if (check_pipe(tmp) == true)
			return (true);
	}
	else if (tmp->type == COMMAND)
	{
		if (check_command(tmp) == true)
			return (true);
	}
	return (false);
}

bool	check_sintax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp->next && (is_space(tmp)))
		tmp = tmp->next;
	if (tmp->type == PIPE)
	{
		error_ex("minishell: syntax error near unexpected token `|'\n");
		return (true);
	}
	while (tmp)
	{
		while (tmp->next && (is_space(tmp)))
			tmp = tmp->next;
		if (ft_sintax_errors(tmp) == true)
			return (true);
		tmp = tmp->next;
	}
	return (tokens = tmp, false);
}
