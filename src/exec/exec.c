/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/22 22:03:52 by root             ###   ########.fr       */
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
		{
		//	print_pipeline(node->pipeline);
			ret = exec_pipeline(node->pipeline);
		}
		sep = node->sep;
		current = current->next;
	}
	return (g_exit_status);
}

int
	exec_command_line(char **tokens)
{
	t_ast	ast;
	//char buffer[10];
//
	//printf("EXEC COMMAND LINE\n");
	//fgets(buffer, 50, stdin);
	if (check_syntax(tokens))
		return (1);
	ast = parse_ast(tokens);
	//print_ast(ast);
//	exit (0);
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
