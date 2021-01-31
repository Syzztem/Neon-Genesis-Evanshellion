/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:06:49 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/31 11:49:25 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

size_t
	add_token(char *token, t_token **list, char *line)
{
	char	*ref;
	char	*tkref;

	ref = line;
	tkref = token;
	while (*ref && !ft_isspace(*ref))
	{
		if (*ref == '\'')
			tkref += squotes(tkref, &ref);
		else if (*ref == '\"')
			tkref += dquotes(tkref, &ref);
		else if (ft_indexof(SEPS, *ref) != -1)
			tkref += seps(tkref, &ref);
		else
			tkref += spaces(tkref, &ref);
	}
	*tkref = '\0';
	ft_lstadd_back((t_list **)list, token);
	return (ref - line);
}
