/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:10:58 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/15 11:32:03 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

void	ft_for_env_var(char *line, t_env *env, int fd)
{
	char	*expanded;

	expanded = ft_expand_envvar(line, env);
	write(fd, expanded, ft_strlen(expanded));
	free (expanded);
}

void	ft_end_heredoc(t_token *tokens)
{
	if (tokens->next && ft_found_heredoc(tokens->next))
		unlink("temp_file.txt");
}

int	ft_check_next_redir(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->next && (token->next->type == REDIR_OUT
				|| token->next->type == REDIR_APPEND
				|| token->next->type == REDIR_IN))
			count++;
		token = token->next;
	}
	return (count);
}
