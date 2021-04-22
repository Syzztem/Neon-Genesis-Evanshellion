/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:41:19 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/22 09:27:42 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ESCAPES ";&|\"<>()\\"

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
	char	*quote;

	ref = line;
	quote = "\0";
	while (*ref)
	{
		if (!*quote && ft_strchr("\"'", *ref))
			quote = ref;
		if (!*quote)
		{
			i = is_sep(ref);
			if (i != -1 && (ref == line || *(ref - 1) != '\\'))
			{
				*sep = (char *)g_seps[i];
				return (ref - line);
			}
		}
		if (ref)
			++ref;
		if (*quote && *ref == *quote)
		{
		//	printf("quote: %s\n", ref);
			ref++;
			quote = "\0";
		}
	}
	*sep = NULL;
	return (ref - line);
}

/*
** static void
** 	clean_backslashes(char **commands)
** {
** 	char	*line;
** 
** 	while (*commands)
** 	{
** 		line = *commands;
** 		while (*line)
** 		{
** 			if (*line == '\\' && ft_indexof(ESCAPES, *line) != -1)
** 				ft_memmove(line, line + 1, ft_strlen(line) + 1);
** 			++line;
** 		}
** 		++commands;
** 	}
** }
** 
*/

char
	**split_line(char *line)
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
	//	printf("out[%zu]: %s\n", i, out[i]);
		line += index;
		++i;
		if (!sep)
			break ;
		out[i] = ft_strdup(sep);
		++i;
		line += ft_strlen(sep);
	}
	out[i] = NULL;
//	clean_backslashes(out);
	return (out);
}
