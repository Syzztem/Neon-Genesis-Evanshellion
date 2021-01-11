/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:34:49 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/11 14:41:11 by lothieve         ###   ########.fr       */
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

/*
static char
	all_match(char *expr, char *entry, size_t ent_len)
{
	size_t i;
	size_t ex_len;

	ex_len = ft_strlen(entry);
	ft_memreplace(expr, '/', '\0', len);
	ft_memreplace(entry, '/', '\0', len);
	i = 0;
	while (i < len)
	{
		if (!matches(expr, entry))
			return (0);
		i += ft_strlen
	}
}
*/

static char
	*cat_path(char *path, char *entry, size_t path_len)
{
	path[path_len] = '/';
	return (ft_strcpy(path + path_len + 1, entry));
}

static int
	get_all_matches(char *expr, char *path, t_token **list)
{
	DIR			*dir;
	t_dirent	*entry;
	size_t		path_len;
		

	dir = opendir(path);
	path_len = ft_strlen(path);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (*entry->d_name == '.')
			continue ;
		cat_path(path, entry->d_name, path_len);
		if (entry->d_type == DT_DIR)
			get_all_matches(expr, path, list);
		if (matches(expr, path + 2))
			ft_lstadd_back((t_list **)list, ft_strdup(path + 2));
		path[path_len] = '\0';
	}
	closedir(dir);
	if (*list)
		return (1);
	return (0);
}

t_token
	*expand_wildcard(char *expr)
{
	char	path[256];
	t_token	*output;

	output = NULL;
	path[0] = '.';
	path[1] = '\0';
	if (get_all_matches(expr, path, &output))
		return (output);
	return (NULL);
}
