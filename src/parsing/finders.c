/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:04:23 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 14:37:01 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char
	**find_token(char *token, char **tokens_table)
{
	ssize_t i;

	i = -1;
	if (!token)
		return (tokens_table + tab_size(tokens_table));
	while (tokens_table[++i])
	{
		if (ft_strcmp(tokens_table[i], token) == 0)
			return (tokens_table + i);
	}
	return (NULL);
}

char
	**find_last_token(char *token, char **tokens_table)
{
	ssize_t i;
	char	**last;

	i = -1;
	last = NULL;
	if (!token)
		return (tokens_table + tab_size(tokens_table));
	while (tokens_table[++i])
	{
		if (ft_strcmp(tokens_table[i], token) == 0)
			last = tokens_table + i;
	}
	return (last);
}

char
	**tab_find_last_token(char **tokens, char **tokens_table)
{
	ssize_t i;
	char	**last;
	char	**current;

	i = -1;
	last = NULL;
	while (tokens[++i])
	{
		current = find_last_token(tokens[i], tokens_table);
		if (current > last)
			last = current;
	}
	return (last);
}

char
	**find_token_in_tokens(char **tokens, char **to_find)
{
	char	**current;

	current = tokens;
	while (!find_token(*current, to_find))
		current++;
	return (current);
}

char
	**safe_find_token(char **tokens, char *find)
{
	char **current;

	current = tokens;
	while (*current && ft_strcmp(find, *current))
		current++;
	return (current);
}
