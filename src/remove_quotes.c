/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:24:50 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/09 11:32:31 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define SQ_ESCAPES " \t\n\v\f\r;&|\"*<>()\\$"
#define DQ_ESCAPES " \t\n\v\f\r;&|\'*<>()"

static size_t
	size_escaped(char *line)
{
	size_t len;

	len = ft_strlen(line);
	while (*line)
	{
		if (ft_indexof(SQ_ESCAPES, *line) != -1)
			++len;
		++line;
	}
	return (len);
}

static size_t
	escape_sq(char *line, char **out)
{
	char *ref;
	char *outref;

	ref = line + 1;
	outref = *out;
	while (*ref != '\'')
	{
		if (ft_indexof(SQ_ESCAPES, *ref) != -1)
		{
			*outref++ = '\\';
		}
		*outref++ = *ref++;
	}
	*out = outref;
	return ((ref - line) + 1);
}

static size_t
	escape_dq(char *line, char **out)
{
	char *ref;
	char *outref;

	ref = line + 1;
	outref = *out;
	while (*ref != '\"' || *(ref - 1) == '\\')
	{
		if (ft_indexof(DQ_ESCAPES, *outref) != -1)
			*outref++ = '\\';
		*outref++ = *ref++;
	}
	*out = outref;
	return ((ref - line) + 1);
}

char
	*remove_quotes(char *line)
{
	char *out;
	char *ref;

	out = malloc(sizeof(char) * (size_escaped(line) + 1));
	ref = out;
	while (*line)
	{
		if (*line == '\'' && line != out && *(line - 1) != '\\')
			line += escape_sq(line, &ref);
		if (*line == '\"' && line != out && *(line - 1) != '\\')
			line += escape_dq(line, &ref);
		*ref++ = *line++;
	}
	*ref = 0;
	return (out);
}
