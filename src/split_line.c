/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:41:19 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/01 15:37:11 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t
	nblines(char *line)
{
	size_t	count;
	uint8_t	i;

	count = 0;
	while (*line)
	{
		i = 0;
		while (g_splitters[i])
		{
			if (strbegin(line, g_splitters[i]))
				count += 2;
			++i;
		}
		++line;
	}
	return (count);
}

static size_t
	next_sep(char *line, char **sep)
{
	char *cpy;

	cpy = line;
	while (*cpy)
	{
		while (g_splitters[i])
		{
			if (strbegin(line, g_splitters[i]))
			{
				*sep = g_splitters[i];
				return (cpy - line);
			}
			++i;
		}
		++cpy;
	}
	*sep = NULL;
	return (cpy - line);
}

char **split_line(char *line)
{
	char	**out;
	size_t	i;
	size_t	index;
	char	*sep;

	out = malloc(sizeof(char *) * (nblines(line) + 1));
	i = 0;
	while (*line)
	{
		index = next_sep(line, &sep);
		out[i] = ft_strndup(line, index);
		line += index;
		++i;
		if (!sep)
			return (out);
		out[i] = ft_strdup(sep);
		++i;
	}
	return (out);
}
