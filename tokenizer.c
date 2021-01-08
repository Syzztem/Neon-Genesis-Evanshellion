/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:50:03 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/08 17:35:36 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_method
	next_token(char *line)
{
	if (*line == '\'')
		return (squotes);
	if (*line == '\"')
		return (dquotes);
	if (ft_indexof(SEPS, *line) != -1)
		return (seps);
	return (spaces);
}

static t_token
	*make_token_list(char *line)
{
	t_token	*head;
	char	*tk;

	head = NULL;
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		tk = next_token(line)(&line);
		ft_lstadd_back((t_list**)&head, tk);
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
