/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_merge_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:57:45 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/19 14:03:26 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

static char	*ft_expander(t_token *next, t_token *curr, t_env *env)
{
	char	*expanded;
	char	*merged;

	expanded = ft_expand_envvar(next->value, env);
	merged = ft_strjoin(curr->value, expanded);
	free(expanded);
	return (merged);
}

int	get_value(t_token *next, t_token *curr, t_env *env, char **merged)
{
	if (next->type == ENV_VAR)
		*merged = ft_expander(next, curr, env);
	else if (next->type == ARGUMENT)
		*merged = ft_strjoin(curr->value, next->value);
	else
		return (-1);
	return (0);
}

void ft_merge_tokens_echo(t_token **tokens, t_env *env)
{
    t_token *curr;
    t_token *next;
    char    *merged;
    int     is_n_option;

    merged = NULL;
    next = NULL;
    is_n_option = 0;
    if (!tokens || !(*tokens))
        return;
    curr = *tokens;
    if (!curr || !curr->next || ft_strcmp(curr->value, "echo") != 0)
        return;
    curr = curr->next;
    while (curr && (curr->type == SPACES || curr->type == GARBAGE))
        curr = curr->next;
    is_n_option = 1;
    if (!curr || curr->type != ARGUMENT || ft_strncmp(curr->value, "-", 1) != 0)
        is_n_option = 0;
    if (is_n_option)
    {
        char *pos = curr->value + 1;
        while (*pos)
        {
            if (*pos != 'n')
            {
                is_n_option = 0;
                break;
            }
            pos++;
        }
        next = curr->next;
        while (is_n_option && next && next->type == ARGUMENT)
        {
            pos = next->value;
            while (*pos)
            {
                if (*pos != 'n')
                {
                    is_n_option = 0;
                    break;
                }
                pos++;
            }
            if (is_n_option)
            {
				merged = ft_strjoin(curr->value, next->value);
                free(curr->value);
                curr->value = merged;
                t_token *to_remove = next;
                next = next->next;
                remove_token_node(tokens, to_remove);
            }
        }
    }
    if (!is_n_option)
    {
        curr = (*tokens)->next;
        while (curr && (curr->type == SPACES || curr->type == GARBAGE))
            curr = curr->next;

        next = curr->next;
        if (!next || next->type == SPACES || next->type == GARBAGE)
            return;

        if (get_value(next, curr, env, &merged) == -1)
            return;

        free(curr->value);
        curr->value = merged;
        remove_token_node(tokens, next);
    }
}

/* void	ft_merge_tokens_echo(t_token **tokens, t_env *env)
{
	t_token	*curr;
	t_token	*next;
	char	*merged;

	merged = NULL;
	next = NULL;
	if (!tokens || !(*tokens))
		return ;
	curr = *tokens;
	if (!curr || !curr->next || ft_strcmp(curr->value, "echo") != 0)
		return ;
	curr = curr->next;
	while (curr && (curr->type == SPACES || curr->type == GARBAGE))
		curr = curr->next;
	if ((!curr || curr->type != ARGUMENT || ft_strncmp(curr->value, "-n", 2))
		&& (ft_strncmp(curr->value, "-", 1) != 0 && curr->next
			&& ft_strncmp(curr->next->value, "n", 1) != 0))
		return ;
	next = curr->next;
	if (!next || next->type == SPACES || next->type == GARBAGE)
		return ;
	if (get_value(next, curr, env, &merged) == -1)
		return ;
	return (free(curr->value),
		curr->value = merged, remove_token_node(tokens, next));
} */
