/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_constants.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:16:52 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 15:31:25 by smaccary         ###   ########.fr       */
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
	**redirects(void)
{
	static char *arr[] = {REDIR_REPLACE, REDIR_APPEND, REDIR_INPUT, NULL};

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
	static char *arr[] = {REDIR_INPUT, NULL};

	return (arr);
}

char
	**pipeline_separators(void)
{
	static char *arr[] = {SEMICOLON, AND, OR, NULL};

	return (arr);
}