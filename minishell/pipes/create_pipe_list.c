/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:40:29 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/16 15:43:59 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"
#include <stdio.h>

t_pipe	*create_pipe_list(t_cmd *cmd, t_token *token)
{
	t_pipe	*current_pipe;
	t_pipe	*head_pipe;

	current_pipe = NULL;
	head_pipe = NULL;
	while (cmd)
	{
		current_pipe = create_pipe_node(cmd, token);
		add_pipe(&head_pipe, current_pipe);
		cmd = cmd->next;
	}
	return (head_pipe);
}

t_pipe	*create_pipe_node(t_cmd *cmd, t_token *head_token)
{
	t_pipe	*node;

	node = malloc (sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->pid = -1;
	node->cmd = cmd;
	node->tokens = head_token;
	node->pipefd[0] = -1;
	node->pipefd[1] = -1;
	node->one_cmd_flag = false;
	node->next = NULL;
	return (node);
}

void	ft_execution_execve(int *fd, char *dir, char **matrix_exe, t_env *env)
{
	if (*fd != 1)
	{
		if (dup2(*fd, STDOUT_FILENO) == -1)
			return (perror("dup2"));
		close (*fd);
	}
	if (dir && execve(dir, matrix_exe, env->env_copy) == -1)
	{
		ft_free_matrix(matrix_exe);
		free(dir);
		env->exit_status = 126;
		perror("execve");
	}
}
//exit(126); dopo perror c era questo
