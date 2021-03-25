/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:27:30 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/24 16:41:46 by smaccary         ###   ########.fr       */
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
	free_cmd(t_command **cmd_ptr)
{
	t_command	*cmd;

	cmd = *cmd_ptr;
	free_to_null((void **)&(cmd->cmd));
	free_tokens(cmd->argv);
	cmd->argv = NULL;
	free_to_null((void **)&(cmd->sep));
	free_tokens(cmd->tokens);
	cmd->tokens = NULL;
	free_tokens(cmd->redirections);
	cmd->redirections = NULL;
	free_to_null((void **)cmd_ptr);
}

void
	free_ast_node(t_ast_node *node)
{
	free_tokens(node->abstract_pipeline);
	node->abstract_pipeline = NULL;
	free_to_null((void **)&node->sep);
}

void
	free_ast(t_ast ast)
{
	ft_lstclear(&ast, (void *)free_ast_node);
}