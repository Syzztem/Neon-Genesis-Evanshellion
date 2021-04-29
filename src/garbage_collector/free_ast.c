/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:32:28 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 19:33:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void
	free_ast_node(t_ast_node *node)
{
	free_tokens(node->abstract_pipeline);
	node->abstract_pipeline = NULL;
	free_pipeline(&(node->pipeline));
	free_to_null((void **)&node->sep);
	free(node);
}

void
	
	free_ast(t_ast ast)
{
	ft_lstclear(&ast, (void *)free_ast_node);
}
