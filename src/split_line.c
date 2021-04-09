/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:41:19 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/09 10:34:59 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	is_sep(char *str)
{
	uint8_t i;

	i = 0;
	while (g_seps[i])
	{
		if (ft_strbegin(str, g_seps[i]))
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

	ref = line;
	while (*ref)
	{
		i = is_sep(ref);
		if (i != -1 && (ref == line || *(ref - 1) != '\\'))
		{
			*sep = (char *)g_seps[i];
			return (ref - line);
		}
		if (ref)
			++ref;
	}
	*sep = NULL;
	return (ref - line);
}

char **split_line(char *line)
{
	char	**out;
	size_t	i;
	size_t	index;
	char	*sep;

	out = malloc(sizeof(char *) * (nblines(line) + 2));
	i = 0;
	while (*line)
	{
		index = next_sep(line, &sep);
		out[i] = ft_strndup(line, index);
		line += index;
		++i;
		if (!sep)
			break ;
		out[i] = ft_strdup(sep);
		++i;
		line += ft_strlen(sep);
	}
	out[i] = NULL;
	return (out);
}
