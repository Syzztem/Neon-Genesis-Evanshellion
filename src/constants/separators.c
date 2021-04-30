/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:16:52 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/30 20:48:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char
	**separators(void)
{
	static char *arr[] = (char *[]){PIPE, SEMICOLON, NULL};

	return (arr);
}

char
	**pipeline_separators(void)
{
	static char *arr[] = {SEMICOLON, AND, OR, NULL};

	return (arr);
}

char
	**connectives(void)
{
	static char *arr[] = {PIPE, AND, OR, REDIR_APPEND, REDIR_REPLACE,
	REDIR_INPUT, REDIR_HERE_DOC, NULL};

	return (arr);
}

char
	**token_separators(void)
{
	static char *arr[] = {REDIR_HERE_DOC, REDIR_APPEND, REDIR_INPUT,
	REDIR_REPLACE, OR, PIPE, SEMICOLON, AND, AMPERSAND, PARENTHESIS_OPEN,
	PARENTHESIS_CLOSE, NULL};

	return (arr);
}
