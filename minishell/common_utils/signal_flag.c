/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:19:24 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/15 14:36:45 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

int	g_signal_flag = 0;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_flag = 130;
	}
}

void	get_exit_status(int status, t_env *env)
{
	int	sig;

	sig = -1;
	if (WIFEXITED(status))
		env->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_printf(2, "Quit (core dumped)\n");
		else if (sig == SIGINT)
			ft_printf(2, "\n");
		env->exit_status = 128 + sig;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
