/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:06:11 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/27 17:01:31 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	spaces(char **line, t_token **list)
{
	size_t	len;
	char	*token;

	len = 0;
	while (**line && !ft_isspace(**line) && ft_indexof(SEPS, **line) == -1)
	{
		len++;
		(*line)++;
		if (**line == '\\' && *((*line) + 1))
		{
			(*line) += 2;
			len += 2;
		}
	}
	token = ft_strndup(*line - len, len);
	if (ft_indexof(token, '*') < 0)
		return (ft_lstadd_back((t_list **)list, token));
	ft_lstmerge((t_list **)list, (t_list *)expand_wildcard(token));
	free(token);
}

void	squotes(char **line, t_token **list)
{
	size_t	len;

	len = 0;
	while (*(++*line) && **line != '\'')
		++len;
	ft_lstadd_back((t_list **)list, ft_strndup(*line - len, len));
	++(*line);
}

void	dquotes(char **line, t_token **list)
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

void	seps(char **line, t_token **list)
{
	size_t	i;

	i = 0;
	while (g_seps[i])
	{
		if (ft_strbegin(*line, g_seps[i]))
		{
			*line += ft_strlen(g_seps[i]);
			ft_lstadd_back((t_list **)list, ft_strdup(g_seps[i]));
			return ;
		}
		i++;
	}
}
