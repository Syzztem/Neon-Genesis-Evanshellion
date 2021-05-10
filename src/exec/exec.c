/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:16:56 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/11 01:10:43 by root             ###   ########.fr       */
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
	int		ret;

	if ((ret = check_syntax(tokens)))
	{
		g_exit_status = 2;
		return (ret);
	}
	ast = parse_ast(tokens);
	if ((ret = check_ast(ast)))
	{
		g_exit_status = 2;
		free_ast(ast);
		return (ret);
	}
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
	ret = exec_command_line(commands);
	free_tokens(commands);
	return (ret);
}
