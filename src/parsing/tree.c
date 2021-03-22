/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:11:30 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 14:24:48 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node
	*node_from_line(char **abstract_pipeline, char *sep)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->abstract_pipeline = abstract_pipeline;
	node->sep = sep;
	return (node);
}

t_ast_node
	*get_next_ast_node(char **tokens)
{
	static char	**current = NULL;
	static char **tokens_start = NULL;
	int			end;
	t_ast_node	*node;

	if (tokens != tokens_start)
	{
		tokens_start = tokens;
		current = tokens;
	}
	if (current == NULL || *current == NULL)
		return (NULL);
	end = get_pipeline_len(current);
	node = node_from_line(dup_n_tab(current, end),
	*find_token_in_tokens(current, PIPELINE_SEPARATORS));
	current += end;
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
		ft_lstadd_back(&lst, node);
	get_next_ast_node(NULL);
	return (lst);
}
