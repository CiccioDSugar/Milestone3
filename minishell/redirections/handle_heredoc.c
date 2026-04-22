/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:57:54 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 11:46:52 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

char	*ft_found_delimiter(t_token *tokens)
{
	while (tokens && tokens->type != DELIMITER)
		tokens = tokens->next;
	if (tokens && tokens->value)
		return (tokens->value);
	return (NULL);
}

bool	ft_exe_heredoc(t_token *tokens, t_env *env, int *fd)
{
	char	*line;
	char	*line_n;
	char	*tmp;

	tmp = ft_strdup(ft_found_delimiter(tokens));
	line_n = ft_strjoin(tmp, "\n");
	free(tmp);
	line = get_next_line(0);
	if (!line && env->exit_status != 127)
	{
		ft_printf(2,
			"minishell: warning:"
			"here-document delimited by end-of-file wanted %s", line_n);
		return (free(line), free(line_n), close(*fd), true);
	}
	if (!ft_strcmp(line, line_n))
		return (free(line), free(line_n), close(*fd), true);
	else if (ft_found_heredoc(tokens))
		ft_for_env_var(line, env, *fd);
	else
		write(*fd, line, ft_strlen(line));
	free (line);
	free(line_n);
	return (false);
}

int	handle_heredoc(t_token *tokens, t_env *env)
{
	int		fd;
	int		saved_stdin;

	saved_stdin = 0;
	fd = open("temp_file.txt", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (ft_check_fd(fd, env) == -1)
		return (-1);
	while (1)
	{
		if (ft_exe_heredoc(tokens, env, &fd))
			return (0);
	}
	return (0);
}
