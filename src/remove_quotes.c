/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:24:50 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/21 10:34:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#define SQ_ESCAPES " \t\n\v\f\r;&|\"*<>()\\$"
#define DQ_ESCAPES " \t\n\v\f\r;&|\'*<>()"

static size_t
	size_escaped(char *line)
{
	size_t len;

	len = ft_strlen(line);
	while (*line)
	{
		if (ft_indexof(SQ_ESCAPES, *line) != -1 || *line == '\'')
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
	//printf("esc sq: %s\n", ref);
	outref = *out;
	while (*ref != '\'')
	{
		/*if (!*ref)
		{
			ft_putendl_fd("minishell: missing matching \'", 2);
			exit(1);
		}*/
		/*if (ft_indexof(SQ_ESCAPES, *ref) != -1)
		{
			*outref++ = '\\';
		}*/
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
		/*if (!*ref)
		{
			ft_putendl_fd("minishell: missing matching \"", 2);
			exit(1);
		}*/
		//if (ft_indexof(DQ_ESCAPES, *ref) != -1)
		//	*outref++ = '\\';
		*outref++ = *ref++;
	}
	*out = outref;
	return ((ref - line) + 1);
}

char
	*remove_quotes(char *line)
{
	char	*out;
	char	*ref;
	char	*lref;

	out = malloc(sizeof(char) * (size_escaped(line) * 2 + 1));
	ref = out;
	lref = line;
	while (*line)
	{
	//	printf("line: %s | out: %s\n", line, out);
		if (*line == '\'' && (line == lref || *(line - 1) != '\\'))
			line += escape_sq(line, &ref);
		else if (*line == '\"' && (line == lref || *(line - 1) != '\\'))
			line += escape_dq(line, &ref);
		else if (*line)
			*ref++ = *line++;
	}
	*ref = 0;
	return (out);
}
