/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:11:30 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/09 02:53:56 by user42           ###   ########.fr       */
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
			current += parenthesis_len(current);
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
	sep = find_pipeline_separator(tokens);
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
	node = node_from_line(current);
	current = find_pipeline_separator(current);
	if (*current)
		current++;
	return (node);
}

int
	is_pipeline_empty(char **pipeline)
{
	char	*first;

	if (!pipeline || !*pipeline)
		return (1);
	if (argv_len(pipeline) != 1)
		return (0);
	first = *pipeline;
	while (*first)
	{
		if (!ft_isspace(*first))
			return (0);
		first++;
	}
	return (1);
}

t_ast
	parse_ast(char **tokens)
{
	t_ast_node	*node;
	t_list		*lst;

	lst = NULL;
	while ((node = get_next_ast_node(tokens)))
	{
		if (!node || is_pipeline_empty(node->abstract_pipeline))
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
