/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:48:36 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/02 10:56:19 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	verify_line(char *line)
{
	char *begin;

	begin = line;
	while (*line)
	{
		if (*line == '\'')
			while (*++line != '\'')
				if (!*line)
					return (0);
		if (*line == '\"')
			while (*line == '\\' || *++line != '\"')
				if (!*line)
					return (0);
		++line;
	}
	return (1);
}

