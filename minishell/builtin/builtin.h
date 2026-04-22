/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:22:18 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/12 17:26:06 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include "../common_utils/common_utils.h"
# include "../redirections/redirections.h"

int		ft_cd(t_cmd *cmd, t_env *env, t_pipe *head);
int		ft_find_export_var(t_env *env, char *args);
void	ft_echo(t_cmd *cmd, t_token *token, t_env *env, t_pipe *head);
void	ft_pwd(t_cmd *cmd, t_env *env, t_pipe *head);
void	ft_unset(t_cmd *cmd, t_env *env, t_pipe *head);
void	ft_exit(t_cmd *cmd, t_env *env, t_pipe *head);
void	ft_env(t_cmd *cmd, t_env *env, t_pipe *head);
void	ft_export(t_cmd *cmd, t_env *env, t_pipe *head);
void	free_all(t_cmd *cmd_list, t_env *env);
void	ft_setenv(const char *key, const char *var, t_env *env);
bool	is_valid_identifier(char *str);

#endif
