/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:50:03 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/12 11:25:30 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_method
	push_next_token(char *line)
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

	head = NULL;
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		push_next_token(line)(&line, &head);
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
