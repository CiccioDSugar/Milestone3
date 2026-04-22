/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:38:56 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/15 12:18:35 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <string.h>

t_cmd	*create_node(char *cmd, t_token *token)
{
	t_cmd	*node;

	node = malloc (sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) + 1);
	ft_bzero(node->args, sizeof(char *));
	node->cmd = ft_strdup(cmd);
	node->pipe_flag = false;
	node->tokens = token;
	node->next = NULL;
	node->input = NULL;
	node->output = NULL;
	node->append = -1;
	node->open_error = false;
	return (node);
}

void	add_command(t_cmd **head, t_cmd *new_token)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (!head | !new_token)
		return ;
	if (*head == NULL)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}
