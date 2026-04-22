/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:32:07 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:33 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <unistd.h>

static t_token	*advance_token_to_arg(t_token *token, int arg_index)
{
	int	count;

	count = -1;
	while (token)
	{
		if (token->type == ARGUMENT || token->type == ENV_VAR
			|| token->type == QUOTE || token->type == EXIT_STATUS)
			count++;
		if (count == arg_index)
			break ;
		token = token->next;
	}
	return (token);
}

static int	ft_check_newline_flag(t_cmd *cmd, int *i)
{
	int	j;
	int	newline;

	newline = 0;
	while (cmd->args[*i])
	{
		if (cmd->args[*i][0] != '-' || cmd->args[*i][1] != 'n')
			break ;
		j = 2;
		while (cmd->args[*i][j] == 'n')
			j++;
		if (cmd->args[*i][j] != '\0')
			break ;
		newline = 1;
		(*i)++;
	}
	return (newline);
}

static void	ft_write_echo(char **args, int fd, t_token *token)
{
	int	i;

	i = 0;
	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		i++;
		token = token->next;
		while (token && token->type == GARBAGE)
			token = token->next;
		if (token && token->type == SPACES && args[i])
			write(fd, " ", 1);
		while (token && token->type == SPACES)
			token = token->next;
		while (token && token->type != ARGUMENT && token->type != QUOTE
			&& token->type != ENV_VAR && token->type != EXIT_STATUS)
			token = token->next;
	}
}

void	ft_echo(t_cmd *cmd, t_token *token, t_env *env, t_pipe *head)
{
	int	fd;
	int	saved_stdin;
	int	i;
	int	newline;

	i = 0;
	saved_stdin = 0;
	newline = 0;
	fd = ft_for_fd(cmd, env, &saved_stdin);
	if (fd == -1 || cmd->open_error)
		return ;
	newline = ft_check_newline_flag(cmd, &i);
	token = advance_token_to_arg(token, i);
	ft_write_echo(&cmd->args[i], fd, token);
	if (!newline)
		write(fd, "\n", 1);
	if (cmd->input)
		restore_sdin(&saved_stdin);
	if (fd != 1)
		close(fd);
	env->exit_status = 0;
	if (cmd->pipe_flag)
		free_all_pipe(head, env);
}
