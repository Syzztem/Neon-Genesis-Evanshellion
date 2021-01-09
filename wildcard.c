/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:34:49 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/09 17:13:55 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <sys/types.h>
#include <dirent.h>
typedef struct dirent t_dirent;

static char
	matches(char *expr, char *entry)
{
	if (*expr == '*' && *entry)
		return (matches(expr + 1, entry) || matches(expr, entry + 1));
	if (*expr == '*')
		return (matches(expr + 1, entry));
	if (*expr && *expr == *entry)
		return (matches(expr + 1, entry + 1));
	if (*expr == *entry)
		return (1);
	return (0);
}

static t_token
	*get_all_matches(char *expr, char foldersonly)
{
	DIR			*dir;
	t_dirent	*entry;
		

	(void)expr;
	dir = opendir(".");
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break;
		if (matches(expr, entry->d_name) && (!foldersonly || entry->d_type == DT_DIR))
			puts(entry->d_name);
	}
	closedir(dir);
	return (NULL);
}

t_token
	*expand_wildcard(char *expr)
{
	return (get_all_matches(expr, 0));
}
