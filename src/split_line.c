/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:41:19 by lothieve          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/02 11:19:47 by smaccary         ###   ########.fr       */
=======
/*   Updated: 2021/04/02 11:21:18 by lothieve         ###   ########.fr       */
>>>>>>> fce33670a4d8adee0326dcd4283ab8319261d1de
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t
	nblines(char *line)
{
	size_t	count;
	uint8_t	i;

	count = 1;
	while (*line)
	{
		i = 0;
		while (g_splitters[i])
		{
			if (ft_strbegin(line, g_splitters[i]))
				count += 2;
			++i;
		}
		++line;
	}
	return (count);
}

static size_t
	skip_quotes(char *str)
{
	char	quote;
	char	*ref;

	ref = str;
	quote = *ref++;
	while (*ref && (*ref != quote || (*(ref - 1) == '\\' && quote == '\"')))
		++ref;
	if (*ref)
		++ref;
	return (ref - str);
}

static size_t
	next_sep(char *line, char **sep)
{
	char *ref;
	uint8_t	i;

	ref = line;
	while (*ref)
	{
		if ((*ref == '\'' || *ref == '\"') && (ref != line && *(ref - 1) != '\\'))
			ref += skip_quotes(ref);
		i = 0;
		while (g_splitters[i])
		{
			if (ft_strbegin(ref, g_splitters[i]))
			{
				*sep = (char *)g_splitters[i];
				return (ref - line);
			}
			++i;
		}
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
