/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:32:58 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:36 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

static void	ft_too_close(int *fd, t_cmd *cmd, int *saved_stdin)
{
	if (*fd != 1)
		close (*fd);
	if (cmd->input)
		restore_sdin(saved_stdin);
}

void	ft_pwd(t_cmd *cmd, t_env *env, t_pipe *head)
{
	char	*pwd;
	int		fd;
	int		saved_stdin;

	saved_stdin = 0;
	pwd = NULL;
	fd = ft_for_fd(cmd, env, &saved_stdin);
	if (fd == -1 || cmd->open_error)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		env->exit_status = 1;
		perror("pwd");
		return ;
	}
	ft_printf(fd, "%s\n", pwd);
	free(pwd);
	ft_too_close(&fd, cmd, &saved_stdin);
	env->exit_status = 0;
	if (cmd->pipe_flag)
		free_all_pipe(head, env);
	return ;
}
