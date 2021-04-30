/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:41:19 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/30 20:45:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ESCAPES ";&|\"<>()\\"

static int
	is_sep(char *str)
{
	uint8_t i;

	i = 0;
	while (token_separators()[i])
	{
		if (ft_strbegin(str, token_separators()[i]))
			return (i);
		++i;
	}
	return (-1);
}

static size_t
	nblines(char *line)
{
	size_t	count;

	count = 1;
	while (*line)
	{
		if (is_sep(line) != -1)
			count += 2;
		++line;
	}
	return (count);
}

static size_t
	next_sep(char *line, char **sep)
{
	char	*ref;
	int		i;
	char	*quote;

	ref = line;
	quote = "\0";
	while (*ref)
	{
		quote = (!*quote && ft_strchr("\"'", *ref)) ? ref : quote;
		if (!*quote)
		{
			i = is_sep(ref);
			if (i != -1 && (ref == line || *(ref - 1) != '\\'))
			{
				*sep = (char *)token_separators()[i];
				return (ref - line);
			}
		}
		ref = (ref) ? ref + 1 : ref;
		if (*quote && *ref == *quote && ++ref)
			quote = "\0";
	}
	*sep = NULL;
	return (ref - line);
}

char
	**split_line(char *line)
{
	char	**out;
	size_t	i;
	size_t	index;
	char	*sep;

	out = malloc(sizeof(char *) * (nblines(line) + 2));
	i = 0;
	while (ft_isspace(*line))
		line++;
	while (*line)
	{
		index = next_sep(line, &sep);
		if (ft_strncmp(line, " ", index))
		{
			out[i] = ft_strndup(line, index);
			++i;
		}
		line += index;
		if (!sep)
			break ;
		out[i++] = ft_strdup(sep);
		line += ft_strlen(sep);
	}
	out[i] = NULL;
	return (out);
}
