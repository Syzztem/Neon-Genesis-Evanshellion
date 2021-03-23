/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:30:20 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/23 16:07:22 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int
	get_last_token(char *tokens)
{
	return (tokens + tab_size(tokens));
}

int
	check_syntax(char **tokens)
{
	puts(get_last_token(tokens));
}

int
	check_ast(t_ast ast)
{
	t_list		*current;
	t_ast_node	*node;
	
	print_ast(ast);
	if (!ast)
		return (1);
//	printf("here ast\n");
	current = ast;
	while (current)
	{
		node = current->content;
		if ((node->sep && ft_strcmp(node->sep, SEMICOLON)) && !current->next)
			return (2);
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
	while (current)
	{
		if (is_redirect(*current))
		{
			if (!current[1])
				return (1);
			if (is_redirect(current[1]))
				return (2);
		}
		current++;
	}
	return (0);
}

int
	check_command(t_command *cmd)
{
	print_command(cmd);
	if (check_redirections(cmd->redirections))
		return (1);
	if (!cmd->argv)
		return (1);
	return (0);
}

int
	check_pipeline(t_pipeline pipeline)
{
	t_list	*current;
	int		err;

	current = pipeline;
//	printf("here pipeline\n");
	while (current)
	{
		err = check_command(current->content);
		if (err)
			return (err);
		current = current->next;
	}
	return (0);
}
