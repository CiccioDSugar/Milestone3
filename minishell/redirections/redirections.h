/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:47:39 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 11:47:05 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "../common_utils/common_utils.h"

t_type	handle_redirection(t_cmd *cmd, t_type type,
			t_token *tokens, t_env *env);
int		handle_redirection_without_command(t_type type,
			t_token *tokens, t_env *env);
int		handle_heredoc(t_token *tokens, t_env *env);
char	*ft_found_delimiter(t_token *tokens);
bool	ft_exe_heredoc(t_token *tokens, t_env *env, int *fd);
int		ft_get_file_name(t_token *head, t_token *tokens,
			t_cmd *cmd, t_type type);
#endif
