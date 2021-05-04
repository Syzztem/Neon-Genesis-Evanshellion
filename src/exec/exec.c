/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/04 13:34:06 by smaccary         ###   ########.fr       */
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
			ret = exec_pipeline(node->pipeline);
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
	if (check_ast(ast))
	{
		free_ast(ast);
		return (1);
	}
	print_ast(ast);
	exec_from_ast(ast);
	free_ast(ast);
	return (g_exit_status);
}

int
	exec_line(char *line)
{
	char	**commands;
	int		ret;

	commands = split_line(line);
	if (!commands)
		return (-1);
	print_argv(commands);
	ret = exec_command_line(commands);
	free_tokens(commands);
	return (ret);
}
