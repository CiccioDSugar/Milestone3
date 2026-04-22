/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:46:05 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:44:30 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"
#include <stdbool.h>
#include <stdio.h>

int	ft_handle_infile_redir(t_token *tokens, t_type type,
	t_env *env, int *saved_stdin)
{
	if (type == REDIR_IN)
	{
		if (handle_input_redirection(tokens->value, saved_stdin) == -1)
			return (-1);
	}
	else if (type == HEREDOC)
	{
		handle_heredoc(tokens, env);
		if (handle_input_redirection("temp_file.txt", saved_stdin) == -1)
			return (-1);
		if (tokens->next)
		{
			if (ft_found_heredoc(tokens->next))
				ft_end_heredoc(tokens);
		}
	}
	return (0);
}

int	handle_redirection_without_command(t_type type,
		t_token *tokens, t_env *env)
{
	int	fd;
	int	saved_stdin;

	saved_stdin = 0;
	fd = 0;
	while (tokens && (tokens->type != FILE_ && tokens->type != DELIMITER))
		tokens = tokens->next;
	if (type == REDIR_OUT)
		fd = open(tokens->value, O_CREAT | O_TRUNC | O_WRONLY | O_RDONLY, 0777);
	if (type == REDIR_IN || type == HEREDOC)
	{
		if (ft_handle_infile_redir(tokens, type, env, &saved_stdin) == -1)
			return (-1);
	}
	if (type == REDIR_APPEND)
		fd = open(tokens->value, O_CREAT | O_APPEND
				| O_WRONLY | O_RDONLY, 0777);
	if (fd == -1)
		return (perror("open"), -1);
	if (fd != 1 && fd != 0)
		close(fd);
	if (type == REDIR_IN || type == HEREDOC)
		restore_sdin(&saved_stdin);
	return (type);
}

bool	ft_get_outfile_name(t_cmd *cmd, t_token *tokens, t_type type)
{
	if (type == REDIR_OUT)
	{
		if (cmd->output)
			free(cmd->output);
		cmd->output = ft_strdup(tokens->value);
		cmd->append = 0;
		return (true);
	}
	else if (type == REDIR_APPEND)
	{
		if (cmd->output)
			free(cmd->output);
		cmd->output = ft_strdup(tokens->value);
		cmd->append = 1;
		return (true);
	}
	return (false);
}

t_type	handle_redirection(t_cmd *cmd, t_type type, t_token *tokens, t_env *env)
{
	t_type	redir_type;

	redir_type = handle_redirection_without_command(type, tokens, env);
	if (redir_type == (t_type)-1)
		return (-1);
	if (!cmd)
		return (redir_type);
	while (tokens && (tokens->type != FILE_ && tokens->type != DELIMITER))
		tokens = tokens->next;
	if (ft_get_outfile_name(cmd, tokens, type))
		return (0);
	else if (type == REDIR_IN)
	{
		if (cmd->input)
			free(cmd->input);
		cmd->input = ft_strdup(tokens->value);
	}
	else if (type == HEREDOC)
	{
		if (cmd->input)
			free(cmd->input);
		cmd->input = ft_strdup("temp_file.txt");
	}
	return (redir_type);
}

int	ft_get_file_name(t_token *head, t_token *tokens, t_cmd *cmd, t_type type)
{
	tokens = head;
	while (tokens && (tokens->type != FILE_ && tokens->type != DELIMITER))
		tokens = tokens->next;
	if (ft_get_outfile_name(cmd, tokens, type))
		return (0);
	else if (type == REDIR_IN)
	{
		if (cmd->input)
			free(cmd->input);
		cmd->input = ft_strdup(tokens->value);
	}
	else if (type == HEREDOC)
	{
		if (cmd->input)
			free(cmd->input);
		cmd->input = ft_strdup("temp_file.txt");
	}
	return (0);
}
