/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:16:40 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/17 18:02:11 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <threads.h>

char	*ft_estatus_to_str(char *value, t_env *env)
{
	int		j;
	char	*before_status;
	char	*post_status;
	char	*e_status;
	char	*result;

	before_status = NULL;
	post_status = NULL;
	j = 0;
	while (value[j] && value[j] != '$')
		j++;
	before_status = ft_substr(value, 0, j);
	j += 2;
	e_status = ft_itoa(env->exit_status);
	post_status = ft_substr(value, j, ft_strlen(value));
	result = ft_strjoin_three(before_status, e_status, post_status);
	free(e_status);
	free(before_status);
	free(post_status);
	return (result);
}

char	**add_args(char **args, char *value, t_type type, t_env *env)
{
	int		i;
	char	**new_args;

	i = ft_matrix_len(args);
	new_args = ft_realloc_mtx(args, ft_matrix_len(args) + 2,
			ft_matrix_len(args));
	if (!new_args)
		return (NULL);
	if (type == ENV_VAR)
		new_args[i++] = ft_expand_envvar(value, env);
	else if (type == EXIT_STATUS)
		new_args[i++] = ft_estatus_to_str(value, env);
	else if (value)
		new_args[i++] = ft_strdup(value);
	else
		new_args[i++] = ft_strdup("");
	new_args[i] = NULL;
	return (new_args);
}

static void	ft_add_node(t_cmd **current, t_token *tokens, t_cmd **head)
{
	*current = create_node(tokens->value, tokens);
	add_command(head, *current);
}

static t_type	ft_exe_redir(t_cmd *current, t_token *tokens, t_env *env)
{
	t_type	redir_type;

	redir_type = handle_redirection(current, tokens->type, tokens, env);
	if (redir_type == (t_type) - 1)
	{
		if (current)
			current->open_error = true;
		return ((t_type) - 1);
	}
	return (redir_type);
}

t_cmd	*create_list(t_token *tokens, t_env *env)
{
	int		redir_before_command;
	t_cmd	*head;
	t_cmd	*current;
	t_type	redir_enum;
	t_token	*head_token;

	head = NULL;
	current = NULL;
	redir_enum = -1;
	head_token = tokens;
	redir_before_command = 0;
	while (tokens)
	{
		if (tokens->type == COMMAND)
		{
			ft_add_node(&current, tokens, &head);
			if (redir_before_command)
			{
				if (redir_enum != (t_type) - 1)
				{
					ft_get_file_name(head_token, tokens, current, redir_enum);
					redir_before_command = 0;
				}
				else
					current->open_error = true;
			}
		}
		else if (is_argument(tokens) && current)
			current->args = add_args(current->args,
					tokens->value, tokens->type, env);
		else if (tokens->type == PIPE)
			current = NULL;
		else if (is_redir(tokens) || tokens->type == HEREDOC)
		{
			redir_enum = ft_exe_redir(current, tokens, env);
			redir_before_command = 1;
			head_token = tokens;
		}
		tokens = tokens->next;
	}
	return (head);
}
