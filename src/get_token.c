/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:06:49 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/28 15:58:10 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

size_t
	add_token(char *token, t_token **list, char *line)
{
	char	*cpy;
	char	*tkcpy;

	cpy = line;
	tkcpy = token;
	while (*cpy && !ft_isspace(*cpy))
	{
		if (*cpy == '\'')
			tkcpy += squotes(tkcpy, &cpy);
		else if (ft_indexof(SEPS, *cpy) != -1)
			tkcpy += seps(tkcpy, &cpy);
		else
			tkcpy += spaces(tkcpy, &cpy);
	}
	ft_lstadd_back((t_list **)list, token);
	return (cpy - line);
}
