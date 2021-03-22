/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapped_finders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:06:23 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 14:18:06 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int
	is_sep(char *token)
{
	return ((int)find_token(token, SEPARATORS));
}

char
	**find_sep(char **tokens)
{
	return (find_token_in_tokens(tokens, SEPARATORS));
}

char
	**find_pipe(char **tokens)
{
	return (safe_find_token(tokens, PIPE));
}

size_t
	get_pipeline_len(char **tokens)
{
	return (find_token_in_tokens(tokens, PIPELINE_SEPARATORS) - tokens);
}

int
	is_redirect(char *token)
{
	return ((int)find_token(token, REDIRECTS));
}
