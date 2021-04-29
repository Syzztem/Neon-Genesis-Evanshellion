/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:30:20 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/30 00:12:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minishell.h"

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

	return (0);
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
	return (0);
}

int
	check_ast(t_ast ast)
{
	t_list		*current;
	t_ast_node	*node;

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
