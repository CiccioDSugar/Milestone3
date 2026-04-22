/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:38:54 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:12:30 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../builtin/builtin.h"
# include "../tokens/tokens.h"
# include "../redirections/redirections.h"
# include "../common_utils/common_utils.h"
# include "../command_list/command.h"
# include "../system_commands/system_commands.h"
# include "../pipes/pipes.h"

void	ft_exe_cmd(t_cmd *cmd_list, t_env *env, t_token *token);
void	ft_main_flow(char **input, t_env **env);
void	ft_token_flow(t_token *tokens, t_env *head_env, t_cmd **cmd);

#endif
