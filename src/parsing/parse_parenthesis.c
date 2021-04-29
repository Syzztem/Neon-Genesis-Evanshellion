/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:15:20 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 00:16:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

size_t
	parenthesis_len(char **tokens)
{
	char		**current;
	unsigned	level;

	if (!tokens || !*tokens)
		return (1);
	current = tokens + 1;
	level = 1;
	while (*current && level)
	{
		if (!ft_strcmp(*current, PARENTHESIS_OPEN))
			++level;
		if (!ft_strcmp(*current, PARENTHESIS_CLOSE))
			--level;
		current++;
	}
	if (level)
	{
		ft_putendl_fd(SHELL_NAME ": missing matching `)'", 2);
		print_argv(tokens);
		exit(1);
		PARGV(tokens);
		return (0);
	}
	return (current - tokens);
}

t_command
	*parse_parenthesis(char **current, size_t *len_ptr)
{
	size_t		end;
	char		**extracted;
	t_command	*command;

	PARGV(current);
	end = parenthesis_len(current);
	if (end == 0)
	{
		printf("RETURNING NULL\n");
		return (NULL);
	}
	extracted = dup_n_tab(current, end);
	command = new_command(ft_strdup(extracted[0]), extracted, NULL);
	//command->tokens = current;
	command->redirections = extract_redirects(current + end);
	if (len_ptr)
		*len_ptr = end;
	return (command);
}
