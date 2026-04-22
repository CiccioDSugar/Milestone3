/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:33:43 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/13 13:56:04 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "../common_utils/common_utils.h"

bool	check_sintax(t_token *tokens);
t_token	*tokenize(char *input, t_env *env);
t_type	get_token_type(char *value, int q_flag, int is_command);
void	add_token(t_token **head, t_token *new_token);
void	assign_token_types(t_token *tokens);
void	mark_sign_spaces(t_token *tokens);
void	ft_merge_tokens_export(t_token **tokens);
void	ft_merge_tokens_echo(t_token **tokens, t_env *env);
bool	check_only_spaces(t_token *tokens);
int		ft_for_quotes(char *input, int *i, int *j, char *buffer);
//handling
bool	handle_quotes(char *input, int *i, char *buffer, t_token **tokens);
bool	handle_quotes(char *input, int *i, char *buffer, t_token **tokens);
bool	handle_special_chars(char *input, int *i,
			char *buffer, t_token **tokens);
bool	handle_word(char *input, int *i, char *buffer, t_token **tokens);
//check sintax
bool	check_redir(t_token *tmp);
bool	check_heredoc(t_token *tmp);
bool	check_pipe(t_token *tmp);
bool	check_command(t_token *tmp);
bool	check_only_spaces(t_token *tokens);

#endif
