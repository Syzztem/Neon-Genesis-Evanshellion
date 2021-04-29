/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:27:30 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/29 19:32:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void
	free_to_null(void **ptr)
{
	if (!ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

void
	free_tokens(char **tokens)
{
	char **current;

	current = tokens;
	if (!current)
		return ;
	while (*current)
	{
		free(*current);
		*current = NULL;
		current++;
	}
	free(tokens);
}

void
	free_cmd(t_command *cmd)
{
	if (cmd->cmd != cmd->argv[0])
		free(cmd->cmd);
	free_tokens(cmd->argv);
	cmd->argv = NULL;
	free_to_null((void **)&(cmd->sep));
	free_tokens(cmd->tokens);
	cmd->tokens = NULL;
	free_tokens(cmd->redirections);
	cmd->redirections = NULL;
	free(cmd);
}

void
	free_pipeline(t_pipeline *pipeline)
{
	ft_lstclear(pipeline, (void *)free_cmd);
}
