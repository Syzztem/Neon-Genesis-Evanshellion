/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:24:39 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 00:25:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char
	**redirects(void)
{
	static char *arr[] = {REDIR_REPLACE, REDIR_APPEND, REDIR_INPUT,
	REDIR_HERE_DOC, NULL};

	return (arr);
}

char
	**output_redirects(void)
{
	static char *arr[] = {REDIR_REPLACE, REDIR_APPEND, NULL};

	return (arr);
}

char
	**input_redirects(void)
{
	static char *arr[] = {REDIR_INPUT, REDIR_HERE_DOC, NULL};

	return (arr);
}
