/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:08:13 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/30 15:09:44 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void
	print_ast_node(t_ast_node *node)
{
	if (!DEBUG && !DEBUG_AST)
		return ;
	printf("  node: %p\n", node);
	printf("    - %-15s", "pipeline:");
	print_argv(node->abstract_pipeline);
	write(1, "\n", 1);
	print_pipeline(node->pipeline);
	printf("    - %-15s", "sep:");
	pesc(node->sep, 1);
	write(1, "\n", 1);
}

void
	print_ast(t_ast ast)
{
	if (!DEBUG && !DEBUG_AST)
		return ;
	printf("ast: %p\n", ast);
	ft_lstiter(ast, (void *)print_ast_node);
    write(1, "\n", 1);
}
