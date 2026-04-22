/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:37:11 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/13 11:57:13 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"
#include <stdbool.h>

t_token	*new_token(const char *value, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	tmp = NULL;
	if (!head | !new_token)
		return ;
	if (*head == NULL)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

bool	exit_status_var(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
			return (true);
		i++;
	}
	return (false);
}

t_type	get_token_type(char *value, int q_flag, int is_command)
{
	if ((value[0] == '\'' || value[0] == '\"') && !ft_find_env_var(value))
		return (QUOTE);
	if (exit_status_var(value) && (q_flag == 0 || q_flag == 2))
		return (EXIT_STATUS);
	if ((ft_find_env_var(value) && (q_flag == 0 || q_flag == 2)))
		return (ENV_VAR);
	if (q_flag == 1 || q_flag == 2 || value[0] == '-')
		return (ARGUMENT);
	if (!ft_strcmp(value, "|"))
		return (PIPE);
	if (!ft_strcmp(value, ">>"))
		return (REDIR_APPEND);
	if (!ft_strcmp(value, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(value, "<"))
		return (REDIR_IN);
	if (!ft_strcmp(value, ">"))
		return (REDIR_OUT);
	if (is_command == 1)
		return (COMMAND);
	return (ARGUMENT);
}

void	remove_token_node(t_token **head, t_token *target)
{
	t_token	*curr;
	t_token	*prev;

	if (!head || !*head || !target)
		return ;
	curr = *head;
	prev = NULL;
	if (curr == target)
	{
		*head = curr->next;
		free(curr->value);
		free(curr);
		return ;
	}
	while (curr && curr != target)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == target)
	{
		prev->next = curr->next;
		free(curr->value);
		free(curr);
	}
}
