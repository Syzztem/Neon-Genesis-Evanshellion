/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:30:20 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/22 23:48:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

char
	**get_last_token(char **tokens)
{
	return (tokens + tab_size(tokens) - 1);
}

int
	check_parenthesis(char **tokens)
{
	char	**current;
	int		is_first_command_token;

	current = tokens;
	is_first_command_token = 1;
	while (*current)
	{
		if (!is_first_command_token && !ft_strcmp(*current, PARENTHESIS_OPEN))
			return (1);
		current++;
		is_first_command_token = 0;
		if (*current && find_token(*current, pipeline_separators()))
		{
			is_first_command_token = 1;
			current++;
		}
	}
	return (0);
}

int
	check_syntax(char **tokens)
{
	char	*last;

	if (!tokens)
	{
		printf("error: TOKENS ARE NULL\n");
		return (1);
	}
	if (!tokens[0])
		return (1);
	if (is_connective(*tokens))
	{
		psyntax_error(*tokens);
		return (1);
	}
	last = *get_last_token(tokens);
	if (is_connective(last))
	{
		psyntax_error(last);
		return (1);
	}
	if (check_parenthesis(tokens))
	{
		psyntax_error(PARENTHESIS_OPEN);
		return (1);
	}
	while (*last)
	{
		if (!ft_isspace(*last))
			return (0);
		last++;
	}
	psyntax_error(get_last_token(tokens)[-1]);
	return (1);
}

int
	check_ast(t_ast ast)
{
	t_list		*current;
	t_ast_node	*node;
	
	//print_ast(ast);
	if (!ast)
	{
		ft_putstr_fd(SHELL_NAME ": unknown syntax error\n", 2);
		return (1);
	}
	current = ast;
	while (current)
	{
		node = current->content;
		if (!((t_ast_node *)(current->content))->abstract_pipeline
		|| !*(((t_ast_node *)(current->content))->abstract_pipeline)
		|| (node->sep && ft_strcmp(node->sep, SEMICOLON) && !current->next))
		{
			psyntax_error(node->sep);
			return (2);
		}
		current = current->next;
	}
	return (0);
}

int
	check_redirections(char **redirections)
{
	char	**current;

	current = redirections;
	if (!current || !*current)
		return (0);
	while (current && *current)
	{
		if (is_redirect(*current))
		{
			if (!current[1] || (!ft_strcmp(current[1], " ") && !current[2]))
			{
				psyntax_error(*current);
				return (1);
			}
			if (is_redirect(current[1]))
			{
				psyntax_error(current[1]);
				return (2);
			}
		}
		current++;
	}
	return (0);
}

int
	check_command(t_command *cmd)
{
	//print_command(cmd);
	if (check_redirections(cmd->redirections))
		return (1);
	if (!cmd->argv)
		return (2);
	return (0);
}

int
	check_pipeline(t_pipeline pipeline)
{
	t_list	*current;
	int		err;

	current = pipeline;
//	printf("here pipeline\n");
//	print_pipeline(pipeline);
	while (current)
	{
		err = check_command(current->content);
		if (err)
			return (err);
		current = current->next;
	}
	return (0);
}
