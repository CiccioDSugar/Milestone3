/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:49:02 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/15 18:39:01 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

static void	ft_set_flag(char *quote, char *input, int *i, int *flag)
{
	*quote = input[(*i)++];
	if (*quote == '\'')
		*flag = 1;
	else
		*flag = 2;
}

int	ft_for_quotes(char *input, int *i, int *j, char *buffer)
{
	char	quote;
	int		flag;

	quote = 0;
	flag = 0;
	if (input[(*i)] == '\'' || input[(*i)] == '"')
	{
		ft_set_flag(&quote, input, i, &flag);
		while (input[(*i)] && input[(*i)] != quote)
		{
			if (input[(*i)] == quote)
				(*i)++;
			else
				buffer[(*j)++] = input[(*i)++];
		}
		if (input[(*i)] == '\0')
			return (-1);
		(*i)++;
		if (j == 0)
			buffer[(*j)++] = '\0';
	}
	else
		buffer[(*j)++] = input[(*i)++];
	return (flag);
}

bool	handle_quotes(char *input, int *i, char *buffer, t_token **tokens)
{
	int		flag;
	int		j;

	j = 0;
	flag = ft_for_quotes(input, i, &j, buffer);
	if (flag == -1)
	{
		error_ex("minishell: QUOTE ERROR\n");
		free_token(*tokens);
		free(buffer);
		return (false);
	}
	buffer[j] = '\0';
	if (j > 0)
		add_token(tokens, new_token(buffer, get_token_type(buffer, flag, 0)));
	return (true);
}

bool	handle_special_chars(char *input, int *i,
					char *buffer, t_token **tokens)
{
	int	j;

	j = 0;
	if (input[(*i)] == '|' || input[(*i)] == '<' || input[(*i)] == '>')
	{
		j = 0;
		if ((input[(*i)] == '<' && input[(*i) + 1] == '<')
			|| (input[(*i)] == '>' && input[(*i) + 1] == '>'))
		{
			buffer[j++] = input[(*i)++];
			buffer[j++] = input[(*i)++];
		}
		else
			buffer[j++] = input[(*i)++];
		buffer[j] = '\0';
		add_token(&(*tokens), new_token(buffer,
				get_token_type(buffer, 0, 0)));
	}
	return (true);
}

bool	handle_word(char *input, int *i, char *buffer, t_token **tokens)
{
	int	j;

	j = 0;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '\'' && input[*i] != '"')
	{
		buffer[j++] = input[(*i)++];
	}
	buffer[j] = '\0';
	if (j > 0)
		add_token(tokens, new_token(buffer, get_token_type(buffer, 0, 0)));
	return (true);
}
