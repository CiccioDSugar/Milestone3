/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:54:55 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:38:05 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "../common_utils/common_utils.h"
# include "../libft/libft.h"
# include "../builtin/builtin.h"
# include "../redirections/redirections.h"
# include "../common_utils/common_utils.h"
# include "../system_commands/system_commands.h"

t_pipe	*create_pipe_node(t_cmd *cmd, t_token *head_tokens);
t_pipe	*create_pipe_list(t_cmd *cmd, t_token *head_tokens);
void	ft_execution_execve(int *fd, char *dir, char **matrix_exe, t_env *env);
void	ft_exe_pipe_cmd(t_pipe *current, t_env *env,
			t_token *token, t_pipe *head);
int		ft_exe_syscmd_in_pipe(t_env *env, t_cmd *cmd);
void	execute_pipe(t_pipe *head_pipe, t_env *env);
void	add_pipe(t_pipe **head, t_pipe *new_token);

#endif
