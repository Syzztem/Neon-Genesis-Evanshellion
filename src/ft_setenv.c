/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:04:08 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/25 17:10:49 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ENV_ALLOC_SIZE 5

static size_t
	env_size(void)
{
	extern char	**environ;
	size_t		i;

	i = 0;
	while (environ[i])
		i++;
	return (i);
}

static size_t
	realloc_env(size_t size)
{
	extern char	**environ;
	char		**sw;

	size += ENV_ALLOC_SIZE;
	sw = ft_calloc(sizeof(char *), size + 1);
	ft_memmove(sw, environ, sizeof(char *) * size);
	free(environ);
	environ = sw;
	return (size);
}

char
	*ft_setenv(char *name, char *value)
{
	extern char		**environ;
	int				env_index;
	static size_t	max_size = 0;

	if (!max_size)
		max_size = env_size();
	env_index = ft_igetenv(name);
	if (env_index == -1)
		env_index = env_size();
	else
		free(environ[env_index]);
	if (max_size >= env_size())
		max_size = realloc_env(max_size);
	puts("");
	environ[env_index] = malloc(sizeof(char) * (ft_strlen(name)
		+ ft_strlen(value) + 2));
	ft_strcpy(environ[env_index], name);
	ft_strcat(environ[env_index], "=");
	ft_strcat(environ[env_index], value);
	environ[env_index + 1] = NULL;
	return (environ[env_index]);
}

void
	copy_env(void)
{
	extern char	**environ;
	char		**sw;
	int			size;
	int			i;

	size = env_size();
	sw = ft_calloc(sizeof(char *), size + 1);
	i = -1;
	while (++i < size)
		sw[i] = ft_strdup(environ[i]);
	environ = sw;
}