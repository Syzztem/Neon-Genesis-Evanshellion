/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:11:30 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/28 23:26:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

char
	**find_pipeline_separator(char **tokens)
{
	char	**current;

	current = tokens;
	while (*current && !find_token(*current, pipeline_separators()))
	{
		if (!ft_strcmp(*current, PARENTHESIS_OPEN))
			current += parenthesis_len(tokens);
		else
			current++;
	}
	return (current);
}

t_ast_node
	*node_from_line(char **tokens)
{
	t_ast_node	*node;
	char		**sep;

	node = ft_calloc(1, sizeof(t_ast_node));
	sep = find_pipeline_separator(tokens);//find_token_in_tokens(tokens, pipeline_separators());
	node->abstract_pipeline = dup_n_tab(tokens, sep - tokens);
	node->pipeline = parse_pipeline(node->abstract_pipeline);
	if (!node->pipeline)
	{
		free_ast_node(node);
		return (NULL);
	}
	if (sep && *sep)
		node->sep = ft_strdup(*sep);
	return (node);
}

t_ast_node
	*get_next_ast_node(char **tokens)
{
	static char	**current = NULL;
	static char **tokens_start = NULL;
	t_ast_node	*node;

	if (tokens != tokens_start)
	{
		tokens_start = tokens;
		current = tokens;
	}
	if (current == NULL || *current == NULL)
		return (NULL);
	PARGV(current);
	node = node_from_line(current);
	current = find_pipeline_separator(current);//find_token_in_tokens(current, pipeline_separators());
	if (*current)
		current++;
	return (node);
}

t_ast
	parse_ast(char **tokens)
{
	t_ast_node	*node;
	t_list		*lst;

	lst = NULL;
	while ((node = get_next_ast_node(tokens)))
	{
		if (!node)
		{
			free_ast(lst);
			lst = NULL;
			break ;
		}
		ft_lstadd_back(&lst, node);
	}
	get_next_ast_node(NULL);
	return (lst);
}
