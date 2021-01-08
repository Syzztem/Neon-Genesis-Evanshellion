/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:06:11 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/08 14:11:31 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*spaces(char **line)
{
	t_token	*out;
	size_t	len;

	len = 0;
	while (**line && !ft_isspace(**line) && ft_indexof(SEPS, **line) == -1)
	{
		len++;
		(*line)++;
	}
	return (ft_strndup(*line - len, len));
}

char	*squotes(char **line)
{
	return (NULL);
}

char	*dquotes(char **line)
{
	return (NULL);
}

char	*seps(char **line)
{
	size_t	i;

	i = 0;
	while (g_seps[i])
	{
		if (ft_strbegin(*line, g_seps[i]))
		{
			*line += ft_strlen(g_seps[i]);
			return (ft_strdup(g_seps[i]));
		}
		i++;
	}
	return (NULL);
}
