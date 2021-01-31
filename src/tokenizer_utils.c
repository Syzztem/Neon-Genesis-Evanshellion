/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:06:49 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/31 14:59:43 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#define PARSE_ERR_COUNT 2
static const char *g_parse_errors[PARSE_ERR_COUNT] = {"Missing matching single quote",
	"Missing matching double quote"};

int
	parse_error(int code)
{
	if (code >= PARSE_ERR_COUNT || code < 0)
		return (1);
	ft_putstr_fd("Parsing Error : ", 2);
	ft_putendl_fd(g_parse_errors[code], 2);
	return (0);
}

int
	verify_line(char *line)
{
	while (*line)
	{
		if (*line == '\'')
			while (*++line != '\'')
				if (!*line)
					return (0);
		if (*line == '\"')
			while (*++line != '\"' || *(line - 1) == '\\')
				if (!*line)
					return (1);
		++line;
	}
	return (-1);
}

size_t
	add_token(char *token, t_token **list, char *line)
{
	char	*ref;
	char	*tkref;

	ref = line;
	tkref = token;
	while (*ref && !ft_isspace(*ref))
	{
		if (*ref == '\'')
			tkref += squotes(tkref, &ref);
		else if (*ref == '\"')
			tkref += dquotes(tkref, &ref);
		else if (ft_indexof(SEPS, *ref) != -1)
			tkref += seps(tkref, &ref);
		else
			tkref += spaces(tkref, &ref);
	}
	*tkref = '\0';
	ft_lstadd_back((t_list **)list, token);
	return (ref - line);
}
