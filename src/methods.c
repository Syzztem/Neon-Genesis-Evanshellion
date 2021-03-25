/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:06:11 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/25 14:36:46 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

size_t
	spaces(char *token, char **line)
{
	char	*tkref;

	tkref = token;
	while (**line && !ft_isspace(**line) && ft_indexof(SEPS, **line) == -1)
	{
		if (**line == '\\' && *(*line + 1))
		{
			++(*line);
			*tkref++ = *(*line)++;
		}
		else
			*tkref++ = *(*line)++;
	}
	return (tkref - token);
}

size_t
	squotes(char *token, char **line)
{
	char *tkref;
	char *ref;

	tkref = token;
	ref = *line;
	ref++;
	while (*ref && *ref != '\'')
	{
		if (*ref == '*')
			*tkref++ = '\\';
		*tkref++ = *ref++;
	}
	*line = ++ref;
	return (tkref - token);
}

size_t
	dquotes(char *token, char **line)
{
	char *tkref;
	char *ref;

	tkref = token;
	ref = *line;
	ref++;
	while (*ref && (*ref != '\"' || *(ref - 1) == '\\'))
	{
		if (*ref == '*')
			*tkref++ = '\\';
		*tkref++ = *ref++;
	}
	*line = ++ref;
	return (tkref - token);
}

size_t
	seps(char *token, char **line)
{
	int	i;
	int sequence;

	i = 0;
	while (g_seps[i])
	{
		if (ft_strbegin(*line, g_seps[i]))
		{
			sequence = i | 0x1b000000;
			ft_memmove(token, &sequence, sizeof(int));
			*line += ft_strlen(g_seps[i]);
			puts(*line);
			return (sizeof(int));
		}
		i++;
	}
	return (0);
}
