/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:32:55 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/20 08:52:06 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct stat	t_stat;

static char
	**split_path(void)
{
	char *path;

	path = ft_getenv("PATH");
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

static char
	*cat_path(char *buf, char *path, char *name)
{
	size_t	path_len;

	path_len = ft_strlen(path);
	ft_strcpy(buf, path);
	buf[path_len] = '/';
	ft_strcpy(buf + path_len + 1, name);
	return (buf);
}

char
	*find_exec(char *path_buf, char *name)
{
	t_stat	buf;
	char	**pathes;
	int		i;

	if (ft_indexof(name, '/') != -1)
		return (name);
	pathes = split_path();
	if (!pathes)
		return (NULL);
	i = -1;
	while (pathes[++i])
	{
		cat_path(path_buf, pathes[i], name);
		if (!stat(path_buf, &buf))
		{
			free_tab(pathes);
			return (path_buf);
		}
	}
	free_tab(pathes);
	return (NULL);
}
