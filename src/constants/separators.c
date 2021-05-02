/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:16:52 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/02 10:28:26 by root             ###   ########.fr       */
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
	static char *arr[] = {OR, PIPE, SEMICOLON, AND, AMPERSAND, PARENTHESIS_OPEN,
	PARENTHESIS_CLOSE, NULL};

	return (arr);
}
