/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzuccaro <fzuccaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:37:37 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 11:46:08 by fzuccaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static void	ft_pipe_flow(t_token *head_token, t_cmd *cmd_head, t_env *env)
{
	t_pipe	*pipe;

	set_pipe_flag(cmd_head);
	pipe = create_pipe_list(cmd_head, head_token);
	execute_pipe(pipe, env);
	free_pipe(pipe);
}

static void	ft_env_var_flow(t_token **tokens, t_env *env)
{
	t_token	*tmp;
	char	*var;

	tmp = *tokens;
	var = NULL;
	while (tmp->type != ENV_VAR && tmp->type != ARGUMENT)
		tmp = tmp->next;
	var = ft_expand_envvar(tmp->value, env);
	ft_printf(1, "%s\n", var);
	free(var);
}

static void	ft_handle_ctrld(t_env *tmp)
{
	rl_clear_history();
	ft_free_matrix(tmp->env_copy);
	free(tmp);
	ft_printf(1, "exit\n");
	close(0);
	close(1);
	close(2);
	exit(0);
}

void	ft_token_flow(t_token *tokens, t_env *head_env, t_cmd **cmd)
{
	t_cmd	*cmd_head;

	cmd_head = *cmd;
	if (!check_sintax(tokens) && !check_only_spaces(tokens))
	{
		if (check_only_env_var(tokens))
			ft_env_var_flow(&tokens, head_env);
		else
		{
			cmd_head = create_list(tokens, head_env);
			if (has_pipe(tokens))
				ft_pipe_flow(tokens, cmd_head, head_env);
			else if (cmd_head)
				ft_exe_cmd(cmd_head, head_env, cmd_head->tokens);
			free_cmd(cmd_head);
		}
	}
}

void	ft_main_flow(char **input, t_env **env)
{
	t_token	*tokens;
	t_cmd	*cmd_head;
	t_env	*tmp;

	tokens = NULL;
	cmd_head = NULL;
	tmp = *env;
	*input = readline("\e[41;30m""minishell> ""\e[0m");
	if (!*input)
		ft_handle_ctrld(tmp);
	if (g_signal_flag == 130)
	{
		tmp->exit_status = 130;
		g_signal_flag = 0;
	}
	if (*input)
		add_history(*input);
	tokens = tokenize(*input, tmp);
	if (tokens)
	{
		ft_token_flow(tokens, tmp, &cmd_head);
		free_token(tokens);
	}
	else
		tmp->exit_status = 2;
}
