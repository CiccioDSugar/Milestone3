/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_merge_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:46:19 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/13 11:58:04 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <string.h>
#include "tokens.h"

static void	ft_merger(t_token **to_delete, t_token *next, char **merged)
{
	char	*tmp;

	tmp = ft_strjoin(*merged, next->value);
	free(*merged);
	*merged = tmp;
	*to_delete = next;
}

static void	ft_merge_word_export(t_token *curr, t_token *next, t_token **tokens)
{
	char	*merged;
	char	*tmp;
	t_token	*to_delete;

	to_delete = NULL;
	tmp = NULL;
	while (curr)
	{
		if (curr->type != ARGUMENT)
		{
			curr = curr->next;
			continue ;
		}
		merged = ft_strdup(curr->value);
		next = curr->next;
		while (next && (next->type == ARGUMENT))
		{
			ft_merger(&to_delete, next, &merged);
			next = next->next;
			remove_token_node(tokens, to_delete);
		}
		free(curr->value);
		curr->value = merged;
		curr = curr->next;
	}
}

void	ft_merge_tokens_export(t_token **tokens)
{
	t_token	*curr;
	t_token	*next;

	curr = NULL;
	next = NULL;
	if (!(*tokens) || !tokens)
		return ;
	curr = *tokens;
	if ((curr->next && (curr->next->type != ARGUMENT
				&& curr->next->type != SPACES && curr->next->type != GARBAGE))
		|| ft_strcmp(curr->value, "export") != 0)
		return ;
	curr = curr->next;
	ft_merge_word_export(curr, next, tokens);
}
