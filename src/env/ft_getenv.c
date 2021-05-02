/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:23:08 by lothieve          #+#    #+#             */
/*   Updated: 2021/05/03 01:00:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int
	env_match(char *name, char *var)
{
	while (*name && *name == *var && *var != '=')
	{
		name++;
		var++;
	}
	if (*var == '=' && !*name)
		return (1);
	return (0);
}

static char
	*env_val(char *env)
{
	while (*env != '=')
		env++;
	env++;
	return (env);
}

char
	*ft_lgetenv(char *line)
{
	extern char **environ;
	size_t		len;
	size_t		i;

	len = 0;
	while (ft_isalnum(line[len]) || line[len] == '_')
		len++;
	i = -1;
	while (environ[++i])
		if (!ft_strncmp(line, environ[i], len) && environ[i][len] == '=')
			return (env_val(environ[i]));
	return (NULL);
}

int
	ft_igetenv(char *name)
{
	extern char **environ;
	size_t		i;

	i = 0;
	while (environ[i])
	{
		if (env_match(name, environ[i]))
			return (i);
		++i;
	}
	return (-1);
}

char
	*ft_getenv(char *name)
{
	extern char **environ;
	int			ret;

	ret = ft_igetenv(name);
	if (ret == -1)
		return (NULL);
	else
		return (env_val(environ[ret]));
}
