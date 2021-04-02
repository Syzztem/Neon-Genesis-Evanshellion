/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:06:49 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/02 10:48:24 by lothieve         ###   ########.fr       */
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

size_t
	add_token(char *token, t_token **list, char *line)
{
	char	*ref;
	char	*tkref;

	ref = line;
	tkref = token;
	while (*ref && !ft_isspace(*ref) && ft_indexof(TOKEN_SPLITTERS, *ref) == -1)
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
