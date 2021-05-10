/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapped_finders_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:22:36 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 23:58:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int
	is_redirect(char *token)
{
	return ((int)find_token(token, redirects()));
}

int
	is_connective(char *token)
{
	return ((int)find_token(token, connectives()));
}

int
	is_sep(char *token)
{
	return ((int)find_token(token, separators()));
}

int
	is_pipeline_sep(char *token)
{
	return ((int)find_token(token, pipeline_separators()));
}
