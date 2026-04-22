/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:29:27 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/17 18:07:42 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	mark_sign_spaces(t_token *tokens)
{
	t_token	*prev;
	int		between_arg;

	prev = NULL;
	between_arg = 0;
	while (tokens)
	{
		if (tokens->type == ARGUMENT || tokens->type == COMMAND
			|| tokens->type == QUOTE || tokens->type == ENV_VAR
			|| tokens->type == PIPE)
		{
			if (between_arg)
				between_arg = 0;
			prev = tokens;
		}
		else if (tokens->type == SPACES)
			ft_assign_spaces(prev, tokens, &between_arg);
		tokens = tokens->next;
	}
}

static int	assign_redir(int *redir_flag, t_token *tokens, int *is_first)
{
	if (*redir_flag)
	{
		while (tokens->next && tokens->type != ARGUMENT)
			tokens = tokens->next;
		tokens->type = FILE_;
		*redir_flag = 0;
		*is_first = 1;//prima era a 0 testare assiduamente
		return (0);
	}
	else if (tokens->type == HEREDOC)
	{
		while (tokens->next && tokens->type != ARGUMENT)
			tokens = tokens->next;
		if (tokens->type != HEREDOC && !is_space(tokens))
			tokens->type = DELIMITER;
		*is_first = 1;//prima era a 0 testare assiduamente
		*redir_flag = 0;
		return (0);
	}
	else if (is_redir(tokens))
	{
		*redir_flag = 1;
		*is_first = 0;
		return (0);
	}
	return (-1);
}

static void	assign_cmd(t_token *tokens, int *is_first)
{
	if (tokens->type == COMMAND || tokens->type == ARGUMENT)
	{
		if (*is_first)
			tokens->type = COMMAND;
		else
			tokens->type = ARGUMENT;
		*is_first = 0;
	}
}

static int	assign_pipe(t_token *tokens)
{
	if (tokens->type == PIPE)
	{
		if (tokens->next)
			tokens = tokens->next;
		if (tokens->type != PIPE)
			assign_token_types(tokens);
		return (0);
	}
	return (-1);
}

void	assign_token_types(t_token *tokens)
{
	int	is_first;
	int	redir_flag;
	int	first_space;

	is_first = 1;
	redir_flag = 0;
	first_space = 1;
	while (tokens)
	{
		if (tokens->type == SPACES || tokens->type == QUOTE)
		{
			if (tokens->type == QUOTE)
				is_first = 0;
			if (tokens->next)
				tokens = tokens->next;
			else
				break ;
			continue ;
		}
		assign_redir(&redir_flag, tokens, &is_first);
		assign_cmd(tokens, &is_first);
		if (assign_pipe(tokens) == 0)
			break ;
		tokens = tokens->next;
	}
}
