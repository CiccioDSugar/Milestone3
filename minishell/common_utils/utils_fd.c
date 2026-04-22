/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:15:12 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 14:29:16 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

int	ft_for_fd(t_cmd *cmd, t_env *env, int *saved_stdin)
{
	int	fd;

	fd = 1;
	if (cmd->input)
	{
		if (handle_input_redirection(cmd->input, saved_stdin) == -1)
			return (-1);
	}
	fd = check_value_fd(cmd->append, cmd->output, env);
	if (ft_check_fd(fd, env) == -1)
		return (-1);
	return (fd);
}

int	ft_check_fd(int fd, t_env *env)
{
	if (fd == -1)
	{
		perror("open");
		env->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	check_value_fd(int append_flag, char *file, t_env *env)
{
	int	fd;

	fd = 0;
	if (append_flag == 1)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (ft_check_fd(fd, env) == -1)
			return (-1);
	}
	else if (append_flag == 0)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (ft_check_fd(fd, env) == -1)
			return (-1);
	}
	else if (append_flag == -1)
		fd = 1;
	return (fd);
}

bool	ft_found_heredoc(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == HEREDOC)
			return (true);
		tokens = tokens->next;
	}
	return (false);
}
