/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:50:03 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/27 02:38:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static size_t
	next_space(char *command)
{
	char *ref;

	ref = command;
	while ((*ref && *ref != SPACE)
			|| (ref != command && *(ref - 1) == '\\'))
		++ref;
	return (ref - command);
}

static size_t
	next_token(char *command)
{
	char *ref;

	ref = command;
	while (*ref != SPACE && (ref == command || *(ref - 1) != '\\'))
		++ref;
	return (ref - command);
}

static size_t
	tok_count(char *command)
{
	size_t	count;

	count = 1;
	while (*command)
	{
		command += next_token(command);
		command += next_space(command);
		++count;
	}
	return (count);
}

void
	clean_backslashes(char **tokens)
{
	char	*line;

	while (*tokens)
	{
		line = *tokens;
		while (*line)
		{
			if (*line == '\\' && *(line + 1) != SPACE)
				ft_memmove(line, line + 1, ft_strlen(line));
			++line;
		}
		++tokens;
	}
}

char
	**tokenize(char *command)
{
	char	**out;
	size_t	i;
	size_t	next;

	out = malloc(sizeof(char *) * (tok_count(command) + 1));
	i = 0;
	while (*command)
	{
		command += next_token(command);
		next = next_space(command);
		if (!next)
			continue ;
		out[i] = ft_strndup(command, next);
		command += next;
		++i;
	}
	out[i] = NULL;
	clean_backslashes(out);
	return (out);
}
