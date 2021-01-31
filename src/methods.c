/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:06:11 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/28 16:45:43 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static
	size_t	sub_env(char *token, char **line)
{
	char	*var;

	++(*line);
	var = ft_lgetenv(*line);
	ft_strcpy(token, var);
	return (ft_strlen(var));
}

size_t	spaces(char *token, char **line)
{
	char	*cpy;

	cpy = token;
	while (**line && !ft_isspace(**line) && ft_indexof(SEPS, **line) == -1)
	{
		if (**line == '\\' && **line + 1)
		{
			++(*line);
			*cpy++ = *(*line++);
			puts(*line);
		}
		else if (**line == '$')
			cpy += sub_env(cpy, line);
		else
			*cpy++ = *(*line)++;
	}
	puts(token);
	return (cpy - token);
}

size_t	squotes(char *token, char **line)
{
	char *tkcpy;
	char *cpy;

	tkcpy = token;
	cpy = *line;
	cpy++;
	while (*cpy && *cpy != '\'')
	{
		if (*cpy == '*')
			*tkcpy++ = '\\';
		*tkcpy++ = *cpy++;
	}
	*line = ++cpy;
	return (tkcpy - token);
}

/*
size_t	dquotes(char *token, char *line)
{
	size_t	len;

	len = 0;
	while (*(++*line) && **line != '\'')
	{
		if (**line == '\\' && *((*line) + 1))
		{
			(*line) += 2;
			len += 2;
		}
		++len;
	}
	ft_lstadd_back((t_list **)list, ft_strndup(*line - len, len));
	++(*line);
}
*/

size_t	seps(char *token, char **line)
{
	size_t	i;

	i = 0;
	while (g_seps[i])
	{
		if (ft_strbegin(*line, g_seps[i]))
		{
			ft_strcpy(token, g_seps[i]);
			i = ft_strlen(g_seps[i]);
			*line += i;
			return (i);
		}
		i++;
	}
	return (0);
}
