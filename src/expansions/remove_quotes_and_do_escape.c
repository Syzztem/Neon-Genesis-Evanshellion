/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_and_do_escape.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:33:31 by root              #+#    #+#             */
/*   Updated: 2021/05/09 03:10:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "vector.h"
#include "minishell.h"
#include "parser.h"

static int
	set_quote(char *to_set, char **quote_ptr, char *new, size_t *index_ptr)
{
	*quote_ptr = to_set;
	if (new && index_ptr)
	{
		new[(*index_ptr)] = '\x1b';
		(*index_ptr)++;
	}
	return (0);
}

static void
	do_copy(char *current, char *quote, char *new, size_t *index_ptr)
{
	if (check_escape(current, quote))
		new[(*index_ptr)++] = '\\';
	new[(*index_ptr)] = *current;
	(*index_ptr)++;
}

static char
	*init_quote_removal(char *line, char **quote_ptr, int *escaped_ptr,
						size_t *i_ptr)
{
	*quote_ptr = "\0";
	*escaped_ptr = 0;
	*i_ptr = 0;
	return (ft_calloc(ft_strlen(line) * 2 + 1, 1));
}

static int
	handle_backslash(char *current, int *escape_ptr)
{
	*escape_ptr = 2;
	return (!ft_strchr(" \"$`", current[1]));
}

char
	*remove_quotes_and_do_escape(char *current, char **end)
{
	char	*quote;
	int		escaped;
	char	*new;
	size_t	i;
	int		copy;

	new = init_quote_removal(current, &quote, &escaped, &i);
	while (new && *current)
	{
		copy = 1;
		if (*quote != '\'' && *current == '\\' && !escaped)
			copy = handle_backslash(current, &escaped);
		else if (escaped && *current == '\\')
			copy = !*quote;
		else if (!escaped && !*quote && ft_strchr("\"'", *current))
			copy = set_quote(current, &quote, new, &i);
		else if (!escaped && *current == *quote)
			copy = set_quote("\0", &quote, NULL, NULL);
		escaped = (*quote != '\'' && *current == '\\' && escaped != 1);
		if (copy)
			do_copy(current, quote, new, &i);
		++current;
	}
	*end = new + i;
	return (new);
}
