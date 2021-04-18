/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/18 18:22:24 by smaccary         ###   ########.fr       */
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
			exec_pipeline(node->pipeline);
		ret = g_exit_status;
		sep = node->sep;
		current = current->next;
	}
	return (g_exit_status);
}

int
	exec_command_line(char **tokens)
{
	t_ast	ast;

	if (check_syntax(tokens))
		return (1);
	ast = parse_ast(tokens);
	print_ast(ast);
	//return 0;
	if (check_ast(ast))
	{
		free_ast(ast);
		return (1);
	}
	exec_from_ast(ast);
	free_ast(ast);
	return (g_exit_status);
}

int
	exec_line(char **commands)
{
	int			ret;

	ret = exec_command_line(commands);
	return (ret);
}
