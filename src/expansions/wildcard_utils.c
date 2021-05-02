/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 20:13:47 by root              #+#    #+#             */
/*   Updated: 2021/05/02 20:14:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

size_t
	wildcard_len(char *command)
{
	int		is;
	char	*ref;

	ref = command;
	is = 0;
	while (*ref && *ref != SPACE)
	{
		if (*ref == '*' && (ref == command || *(ref - 1) != '\\'))
			is = 1;
		++ref;
	}
	if (is)
		return (ref - command);
	return (0);
}

size_t
	add_wildcard(char *command, size_t len, t_token **list)
{
	ft_lstmerge((t_list **)list, (t_list *)
			expand_wildcard(ft_strndup(command, len)));
	return (len);
}
