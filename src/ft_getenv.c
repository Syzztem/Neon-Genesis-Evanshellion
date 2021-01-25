/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:23:08 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/25 17:12:36 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ENV_ALLOC_SIZE 5
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
