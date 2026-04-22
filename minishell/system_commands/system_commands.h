/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_commands.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:06:04 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:08:17 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_COMMANDS_H
# define SYSTEM_COMMANDS_H

# include "../libft/libft.h"
# include "../common_utils/common_utils.h"
# include "../redirections/redirections.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_path_finder(t_env *env, t_cmd *cmd);
int		ft_exe_syscmd(t_env *env, t_cmd *cmd);
char	**ft_mtx_cmd(t_cmd *cmd);
#endif
