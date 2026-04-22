/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:57:20 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/13 10:50:48 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "../common_utils/common_utils.h"
# include "../tokens/tokens.h"
# include "../redirections/redirections.h"

char	**add_args(char **args, char *value, t_type type, t_env *env);
void	add_command(t_cmd **head, t_cmd *new_token);
t_cmd	*create_list(t_token *tokens, t_env *env);
t_cmd	*create_node(char *cmd, t_token *token);

#endif
