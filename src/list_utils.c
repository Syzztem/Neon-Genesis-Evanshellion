/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:41:36 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/15 14:25:14 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#define ESCAPES "*$"

static size_t
	total_len(t_token *list)
{
	if (list)
		return (total_len(list->next) + ft_strlen(list->token) + 1);
	return (0);
}

static char
	*copy_and_epurate(char *dst, char *src)
{
	while (*src)
	{
		if (*src == '\\' && ft_indexof(ESCAPES, *(src + 1)) != -1)
			++src;
		*dst++ = *src++;
	}
	return (dst);
}

char
	*list_to_pure_string(t_token *list)
{
	char *out;
	char *ref;

	out = malloc(sizeof(char) * (total_len(list) + 1));
	ref = out;
	while (list)
	{
		ref = copy_and_epurate(ref, list->token);
		*ref++ = ' ';
		list = list->next;
	}
	*ref = '\0';
	return (out);
}

void
	print_list(t_token *list)
{
	if (list)
	{
		puts(list->token);
		print_list(list->next);
	}
}

void
	free_list(t_token *list)
{
	if (!list)
		return ;
	free_list(list->next);
	free(list->token);
	free(list);
}