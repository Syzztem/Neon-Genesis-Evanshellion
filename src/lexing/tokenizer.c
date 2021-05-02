/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:07:44 by user42            #+#    #+#             */
/*   Updated: 2021/05/02 12:07:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "vector.h"

static char
	*init_tokenizing(char *str, char **current, char **start, int *skip)
{
	if (*start != str)
	{
		*start = str;
		*current = str;
	}
	if (!str)
		return (NULL);
	*skip = 0;
	while (**current == SPACE || (**current == '\\' && (*current)[1] == SPACE))
		(*current)++;
	if (!**current)
		return (NULL);
	return (*current);
}

void
	move_to_next_quote(char **current, int *skip)
{
	while (**current && (*skip || !ft_strchr("\"' <>", **current)))
	{
		*skip = (**current == '\\' && ft_strchr("\"' <>", (*current)[1]));
		(*current)++;
	}
}

int
	move_to_quote_end(char **current, int *skip)
{
	char	*quote;

	if (ft_strchr("\"'", *(*current)))
	{
		quote = (*current);
		(*current)++;
		while (*(*current) != *quote || *skip)
		{
			*skip = 0;
			if (*(*current) == 0)
				return (0);
			if ((*current)[0] == '\\' && (*current)[1] == '\\')
				(*current) += 2;
			else
			{
				*skip = (*quote != '\'' && *(*current) == '\\'
						&& (*current)[1] == *quote);
				(*current)++;
			}
		}
		(*current)++;
	}
	return (1);
}

char
	*get_next_token(char *str)
{
	static char	*current = NULL;
	static char	*start = NULL;
	char		*begin;
	int			skip;

	if (!(begin = init_tokenizing(str, &current, &start, &skip)))
		return (NULL);
	if (ft_strchr("<>", *current))
	{
		while (ft_strchr("<>", *current))
			current++;
		return (ft_strndup(begin, current - begin));
	}
	while (*current && *current != SPACE)
	{
		if (!move_to_quote_end(&current, &skip))
			return (NULL);
		move_to_next_quote(&current, &skip);
		if (ft_strchr("<>", *current))
			break ;
	}
	return (ft_strndup(begin, current - begin));
}

char
	**split_quotes(char *str)
{
	t_vector	*v;
	char		*current;
	char		*new_token;
	char		**splitted;

	current = str;
	v = new_vector(10, sizeof(char **));
	while ((new_token = get_next_token(str)))
		vector_append(v, &new_token, 1);
	get_next_token(NULL);
	vector_append(v, &new_token, 1);
	splitted = v->bytes;
	free(v);
	return (splitted);
}
