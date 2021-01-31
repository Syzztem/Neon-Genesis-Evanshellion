/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:50:03 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/31 13:10:47 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static size_t
	token_len(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (ft_indexof(line, '$') == -1)
		return (len);
	while (*line)
	{
		if (*line == '$')
			len += ft_strlen(ft_lgetenv(line + 1));
		else if (*line == '\"')
			while (*++line && *(line - 1) != '\\' && *line != '\"')
				;
		else if (*line == '\'')
			while (*++line != '\'')
				;
		else if (*line == '*')
			len++;
		line++;
	}
	return (len);
}

static t_token
	*make_token_list(char *line)
{
	t_token	*head;
	size_t	tok_len;
	char	*token;

	head = NULL;
	tok_len = token_len(line);
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		token = ft_calloc(sizeof(char), tok_len + 1);
		line += add_token(token, &head, line);
	}
	return (head);
}

static char
	**to_tab(t_token *list)
{
	char	**out;
	size_t	size;
	size_t	i;

	size = ft_lstsize((t_list *)list);
	out = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (list)
	{
		out[i] = list->token;
		i++;
		list = list->next;
	}
	out[i] = NULL;
	return (out);
}

static void
	free_list(t_token *list)
{
	if (list)
		free_list(list->next);
	free(list);
}

char
	**tokenize(char *line)
{
	t_token	*tokens;
	char	**out;

	tokens = make_token_list(line);
	out = to_tab(tokens);
	free_list(tokens);
	return (out);
}
