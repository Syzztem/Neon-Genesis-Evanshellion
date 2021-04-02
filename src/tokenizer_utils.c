/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:06:49 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/02 15:07:12 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#define PARSE_ERR_COUNT 2

static int
	is_wildcard(char *token)
{
	if (*token == '*')
		return (1);
	while (*token)
	{
		if (*token != '\\' && *(token + 1) == '*')
			return (1);
		++token;
	}
	return (0);
}

static void
	epurate_wildcards(char *token)
{
	while (*token)
	{
		if (*token == '\\' && *(token + 1) == '*')
			ft_memmove(token, token + 1, ft_strlen(token));
		++token;
	}
}

static size_t
	handle_parenthesis(char *token, t_token **list, char *line)
{
	char *ref;

	ref = line;
	ft_lstadd_back((t_list **)list, ft_strdup("("));
	++ref;
	ft_lstadd_back((t_list **)list, token);
	while (*ref && (*ref != ')' || (ref != line && *(ref - 1) == '\\')))
		*token++ = *ref++;
	ft_lstadd_back((t_list **)list, ft_strdup(")"));
	return (++ref - line);
}

size_t
	add_token(char *token, t_token **list, char *line)
{
	char	*ref;
	char	*tkref;

	ref = line;
	tkref = token;
	if (*line == '(')
		return (handle_parenthesis(token, list, line));
	while (*ref && ft_indexof(TOKEN_SPLITTERS, *ref) == -1)
	{
		if (*ref == '\'')
			tkref += squotes(tkref, &ref);
		else if (*ref == '\"')
			tkref += dquotes(tkref, &ref);
		else
			tkref += spaces(tkref, &ref);
	}
	if (ft_indexof(TOKEN_SPLITTERS, *ref) != -1 && tkref == token)
		tkref += seps(tkref, &ref);
	*tkref = '\0';
	if (is_wildcard(token))
		ft_lstmerge((t_list **)list, (t_list *)expand_wildcard(token));
	else
		ft_lstadd_back((t_list **)list, token);
	epurate_wildcards(token);
	return (ref - line);
}
