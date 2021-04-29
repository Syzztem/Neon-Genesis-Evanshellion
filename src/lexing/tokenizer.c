/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:07:44 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 21:08:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "vector.h"

char
	*get_next_token(char *str)
{
	static char	*current = NULL;
	static char	*start = NULL;
	char		*begin;
	char		*quote;
	int			skip;

	if (start != str)
	{
		start = str;
		current = str;
	}
	if (!str)
		return (NULL);
	skip = 0;
	while (*current == SPACE || (*current == '\\' && current[1] == SPACE))
		current++;
	if (!*current)
		return (NULL);
	begin = current;
	while (*current && *current != SPACE)
	{
		if (ft_strchr("\"'", *current))
		{
			quote = current;
			current++;
			while (*current != *quote || skip)
			{
				skip = 0;
				if (*current == 0)
					return (NULL);
				if (current[0] == '\\' && current[1] == '\\')
					current += 2;
				else
				{
					skip = (*quote != '\'' && *current == '\\'
							&& current[1] == *quote);
					current++;				
				}
			}
			current++;
		}
		while (*current && (skip || !ft_strchr("\"' ", *current)))
		{
			skip = (*current == '\\' && ft_strchr("\"' ", current[1]));
			current++;
		}
	}
	return (ft_strndup(begin, current - begin));
}

char
	**split_quotes(char	*str)
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
