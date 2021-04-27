/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:24:50 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/27 07:46:43 by root             ###   ########.fr       */
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
	outref = *out;
	while (*ref != '\'')
		*outref++ = *ref++;
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
	while (*ref != '\"' )
	{
		if (!*ref)
		{
			ref[-1] = 0;
			ft_strcpy(*out, line + 1);
			*out = ft_strchr(*out, 0);
			return (ref - line + 1);
		}
		ref++;
	}
	ref = line + 1;
	while (*ref != '\"')
		*outref++ = *ref++;
	*out = outref;
	return ((ref - line) + 1);
}

/*
** char
** 	*remove_quotes(char *line)
** {
** 	char	*out;
** 	char	*ref;
** 	char	*lref;
** 
** 	out = malloc(sizeof(char) * (size_escaped(line) * 2 + 1));
** 	ref = out;
** 	lref = line;
** 	while (*line)
** 	{
** 		if (*line == '\'' && (line == lref || *(line - 1) != '\\'))
** 			line += escape_sq(line, &ref);
** 		else if (*line == '\"' && (line == lref || *(line - 1) != '\\'))
** 		{
** 			line += escape_dq(line, &ref);
** 
** 		}
** 		else if (*line)
** 			*ref++ = *line++;
** 	}
** 	*ref = 0;
** 	return (out);
** }
*/

#define TO_ESCAPE "|;&<>$"

/*
** char
** 	*remove_quotes(char *line)
** {
** 	char	*current;
** 	char	*quote;
** 	int		escaped;
** 	char	*new;
** 	size_t	i;
** 	int		copy;
** 
** 	current = line;
** 	quote = "\0";
** 	escaped = 0;
** 	new = ft_calloc(ft_strlen(line) + 1, 1);
** 	i = 0;
** 	while (*current)
** 	{
** 		copy = 1;
** 		if (*quote != '\'' && *current == '\\' && !escaped)
** 		{
** 			escaped = 1;
** 			copy = *quote;
** 		}
** 		else if (escaped && *current == '\\')
** 		{
** 			escaped = 0;
** 			copy = !*quote;
** 		}
** 		else if ((!escaped && !*quote && ft_strchr("\"'", *current)))
** 		{
** 			quote = current;
** 			copy = 0;
** 		}
** 		else if (!escaped && *quote && *current == *quote)
** 		{
** 			copy = 0;
** 			quote = "\0";
** 			escaped = 0;
** 		}
** 		if (copy)
** 		{
** 			new[i] = *current;
** 			i++;
** 		}
** 		++current;
** 		escaped = 0;
** 	}
** 	return (new);
** }
*/


char
	*remove_quotes(char *line)
{
	char	*current;
	char	*quote;
	int		escaped;
	char	*new;
	size_t	i;
	int		copy;

	current = line;
	quote = "\0";
	escaped = 0;
	new = ft_calloc(ft_strlen(line) + 1, 1);
	i = 0;

	int a,b,c,d;
	while (*current)
	{
		copy = 1;
		a = (*quote != '\'' && *current == '\\' && !escaped);
		//b = (*quote == '\'' || *current != '\\' || escaped) && escaped && *current == '\\';
		b = escaped && *current == '\\';
		//c = !b &&  (!escaped && !*quote && ft_strchr("\"'", *current));
		c = !escaped && !*quote && ft_strchr("\"'", *current);
		//d = !c && (!escaped && *quote && *current == *quote);
		d = !escaped && *current == *quote;
		if (a)
			copy = *quote && current[1] != *quote;
		if (b)
			copy = !*quote;
		if (c)
		{
			quote = current;
			copy = 0;
		}
		if (d)
		{
			quote = "\0";
			copy = 0;
		}
		escaped = (*quote != '\'' && *current == '\\' && !escaped);
		if (copy)
		{
			new[i] = *current;
			i++;
		}
		++current;
	}
	return (new);
}
