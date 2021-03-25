/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:11:30 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/24 16:46:14 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node
	*node_from_line(char **abstract_pipeline, char *sep)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	node->abstract_pipeline = abstract_pipeline;
	if (sep)
		node->sep = ft_strdup(sep);
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
	*find_token_in_tokens(current, pipeline_separators()));
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
