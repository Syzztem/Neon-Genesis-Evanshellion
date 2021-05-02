/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:28:36 by root              #+#    #+#             */
/*   Updated: 2021/05/02 20:36:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "vector.h"
#include "minishell.h"
#include "parser.h"

static size_t
	next_space(char *command)
{
	char *ref;

	ref = command;
	while (*ref && ((!ft_isspace(*ref)
			|| (ref != command && *(ref - 1) == '\\'))))
		++ref;
	return (ref - command);
}

static size_t
	next_token(char *command)
{
	char *ref;

	ref = command;
	while (ft_isspace(*ref) && (ref == command || *(ref - 1) != '\\'))
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

static void
	clean_backslashes(char **tokens)
{
	char	*line;
	char	*found;

	while (*tokens)
	{
		line = *tokens;
		while (*line)
		{
			if (*line == '\x1b')
			{
				ft_memmove(line, line + 1, ft_strlen(line));
				continue;
			}
			found = ft_strchr(SQ_ESCAPES "'", line[1]);
			if (*line == '\\' && found && *found)
				ft_memmove(line, line + 1, ft_strlen(line));
			++line;
		}
		++tokens;
	}
}

char
	**tokenize(char *command, char *end)
{
	char	**out;
	size_t	i;
	size_t	next;

	if (!(out = ft_calloc((tok_count(command) + 1), sizeof(char *))))
		return (NULL);
	i = 0;
	while (command < end)
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
