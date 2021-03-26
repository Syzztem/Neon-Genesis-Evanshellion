/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:06:11 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/25 17:31:26 by smaccary         ###   ########.fr       */
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
	//int sequence;

	i = 0;
	while (g_seps[i])
	{
		if (ft_strbegin(*line, g_seps[i]))
		{

		/*
			sequence = i | 0x1b000000;
			ft_memmove(token, &sequence, sizeof(int));
		 						
			This does not provide me tokens my parser can use.
			For example: a pipe will give sequence = 0x3 | 0x1b000000 = 0x1b0000003
			that means the token will look like the following when viewed a char array/string : {ESC, '\0', '\0', '|', '\0'};
			The string is broken at token[1], meaning all string based functions will ignore everything after that
			It is much more practical to just add the ESC character at tokens's start followed by the separator as plain text.
		*/
			token[0] = 27;
			ft_memmove(token + 1, g_seps[i], ft_strlen(g_seps[i]));
			token[1 + ft_strlen(g_seps[i])] = 0;
			*line += ft_strlen(g_seps[i]);
		//	puts(*line);
			return (ft_strlen(token));
		}
		i++;
	}
	return (0);
}
