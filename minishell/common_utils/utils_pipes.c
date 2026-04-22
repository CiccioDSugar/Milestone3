/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:51 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/13 18:36:12 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common_utils.h"

void	restore_sdin(int *saved_stdin)
{
	dup2(*saved_stdin, 0);
	close (*saved_stdin);
}

int	handle_input_redirection(char *input_file, int	*saved_stdin)
{
	int	fd;

	fd = 0;
	if (!input_file)
		return (0);
	*saved_stdin = dup(0);
	if (*saved_stdin < 0)
		return (perror("dup"), -1);
	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		return (perror(input_file), close(*saved_stdin), -1);
	if (dup2(fd, 0))
		return (close(fd), perror("dup2"), close(*saved_stdin), -1);
	return (close(fd), 1);
}

void	add_pipe(t_pipe **head, t_pipe *pipe)
{
	t_pipe	*tmp;

	tmp = NULL;
	if (!head | !pipe)
		return ;
	if (*head == NULL)
		*head = pipe;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = pipe;
	}
}

bool	has_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
			return (true);
		token = token->next;
	}
	return (false);
}

void	set_pipe_flag(t_cmd *head)
{
	t_cmd	*tmp;

	tmp = head;
	while (head)
	{
		head->pipe_flag = true;
		head = head->next;
	}
	head = tmp;
}

/* void print_pipes(t_pipe *pipe)
{
	while (pipe)
	{
		printf("pipe: [%d] - Type: [%s]\n", pipe->pid, pipe->cmd->cmd);
		pipe = pipe->next;
	}
} */
