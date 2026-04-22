/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:00:05 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/15 17:39:07 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <readline/chardefs.h>
#include <stdbool.h>

void	ft_define_tokens(t_token *tokens, t_env *env)
{
	assign_token_types(tokens);
	mark_sign_spaces(tokens);
	ft_merge_tokens_export(&tokens);
	ft_merge_tokens_echo(&tokens, env);
}

int	ft_get_tokens(char *input, int *i, t_token **tokens, char **buffer)
{
	while (ft_isspace(input[(*i)]))
	{
		add_token(tokens, new_token(" ", SPACES));
		(*i)++;
	}
	if (input[(*i)] == '\0')
		return (0);
	if (input[(*i)] == '\'' || input[(*i)] == '"')
	{
		if (!handle_quotes(input, i, *buffer, tokens))
			return (-1);
	}
	else if (input[(*i)] == '|' || input[(*i)] == '<' || input[(*i)] == '>')
	{
		if (!handle_special_chars(input, i, *buffer, tokens))
			return (-1);
	}
	else
	{
		if (!handle_word(input, i, *buffer, tokens))
			return (-1);
	}
	return (0);
}

t_token	*tokenize(char *input, t_env *env)
{
	int		i;
	char	*buffer;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	buffer = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!buffer)
		return (NULL);
	while (ft_isspace(input[i]))
		i++;
	while (input[i])
	{
		if (ft_get_tokens(input, &i, &tokens, &buffer) == -1)
			return (NULL);
		if (input[i] == '\0')
			break ;
	}
	free(buffer);
	ft_define_tokens(tokens, env);
	return (tokens);
}
