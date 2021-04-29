/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapped_finders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:06:23 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/30 00:23:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char
	**find_sep(char **tokens)
{
	return (find_token_in_tokens(tokens, separators()));
}

char
	**find_pipe(char **tokens)
{
	return (safe_find_token(tokens, PIPE));
}

size_t
	get_pipeline_len(char **tokens)
{
	return (find_token_in_tokens(tokens, pipeline_separators()) - tokens);
}
