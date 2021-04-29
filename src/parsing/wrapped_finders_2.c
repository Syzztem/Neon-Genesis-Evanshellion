/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapped_finders_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:22:36 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 00:23:06 by user42           ###   ########.fr       */
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
