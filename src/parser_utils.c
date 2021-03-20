/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:14:23 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/20 18:23:13 by smaccary         ###   ########.fr       */
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

int
	is_sep(char *token)
{
	return ((int)find_token(token, SEPARATORS));
}

/*
char
	**find_pipeline_sep(char **tokens)
{
	char **current;
	
	current = tokens;
	while (!find_token(*current, PIPELINE_SEPARATORS))
		current++;
	return (current);
}
*/

char
	**find_token_in_tokens(char **tokens, char **to_find)
{
	char **current;
	
	current = tokens;
	while (!find_token(*current, to_find))
		current++;
	return (current);	
}

char
	**find_sep(char **tokens)
{
	return (find_token_in_tokens(tokens, SEPARATORS));
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

char
	**find_pipe(char **tokens)
{
	return (safe_find_token(tokens, PIPE));
}

size_t
	get_pipeline_len(char **tokens)
{
	return (find_sep(tokens) - tokens);
}

size_t
	get_command_len(char **tokens)
{
	return (find_pipe(tokens) - tokens);
}

char
	**dup_n_tab(char **table, size_t n)
{
	char		**dup;
	size_t		size;
	size_t		i;

	size = tab_size(table);
	if (n < size)
		size = n;
	dup = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (i < size)
	{
		dup[i] = ft_strdup(table[i]);
		i++;
	}
	return (dup);
}

int
	count_cmd(char **tokens)
{
	int		count;
	char	**current;

	current = tokens;
	count = 1;
	while (*current)
	{
		if (is_sep(*current))
			count++;
		current++;	
	}
	return (count);
}
