/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:39:26 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/15 14:29:03 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*input;

	input = NULL;
	env = malloc(sizeof(t_env));
	if (!env)
		return (-1);
	(void)ac;
	(void)av;
	env->env_copy = NULL;
	env->path_deleted = false;
	env->env_copy = ft_dup_matrix(envp, env->env_copy);
	env->exit_status = 0;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		ft_main_flow(&input, &env);
		unlink("temp_file.txt");
	}
	free(input);
	return (0);
}
