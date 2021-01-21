/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:34:49 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/12 17:45:43 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <sys/types.h>
#include <dirent.h>

typedef struct dirent	t_dirent;

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

static char
	all_matches(char **expr, char *entry)
{
	char	**ent_split;
	size_t	i;

	ent_split = ft_split(entry, '/');
	i = -1;
	while (expr[++i] && ent_split[i])
	{
		if (!matches(expr[i], ent_split[i]))
			break ;
	}
	if (expr[i] == ent_split[i])
		return (ft_free_tab(ent_split) + 1);
	return (ft_free_tab(ent_split));
}

static char
	*cat_path(char *path, char *entry, size_t path_len)
{
	path[path_len] = '/';
	return (ft_strcpy(path + path_len + 1, entry));
}

static int
	get_all_matches(char **expr, char *path, t_token **list)
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
		cat_path(path, entry->d_name, path_len);
		if (*entry->d_name != '.' && entry->d_type == DT_DIR)
			get_all_matches(expr, path, list);
		if (*entry->d_name != '.' && all_matches(expr, path + 2))
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
	char	**exp_split;
	char	path[256];
	t_token	*output;

	output = NULL;
	path[0] = '.';
	path[1] = '\0';
	exp_split = ft_split(expr, '/');
	if (get_all_matches(exp_split, path, &output))
	{
		ft_free_tab(exp_split);
		return (output);
	}
	ft_free_tab(exp_split);
	ft_putstr_fd("minishell: no matches found : ", 2);
	ft_putendl_fd(expr, 2);
	return (NULL);
}
