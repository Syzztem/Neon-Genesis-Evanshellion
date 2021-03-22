/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 13:59:34 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

int
	exec_from_ast(t_ast ast)
{
	t_list		*current;
	t_ast_node	*node;
	char		*sep;
	int			ret;

	current = ast;
	ret = 0;
	sep = NULL;
	while (current)
	{
		node = current->content;
		if (check_pipeline_run(sep, ret))
			exec_abstract_pipeline(node->abstract_pipeline);
		ret = g_exit_status;
		sep = node->sep;
		current = current->next;
	}
	return (g_exit_status);
}

void
	free_ast(t_ast ast)
{
	(void)ast;
	return ;
}

int
	exec_command_line(char **tokens)
{
	t_ast	ast;

	ast = parse_ast(tokens);
	exec_from_ast(ast);
	free_ast(ast);
	return (g_exit_status);
}
