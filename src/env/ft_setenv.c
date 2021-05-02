/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:04:08 by lothieve          #+#    #+#             */
/*   Updated: 2021/05/03 00:56:38 by root             ###   ########.fr       */
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
	realloc_env(void)
{
	extern char	**environ;
	char		**sw;
	size_t		size;

	size = env_size() + ENV_ALLOC_SIZE;
	sw = ft_calloc(sizeof(char *), size + 1);
	ft_memmove(sw, environ, sizeof(char *) * (size - ENV_ALLOC_SIZE));
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

	if (!ft_strlen(name))
	{
		p_builtin_error("export", value, "not a valid identifier");
		return (NULL);
	}
	if (!max_size)
		max_size = env_size();
	env_index = ft_igetenv(name);
	if (env_index == -1)
		env_index = env_size();
	else
		free(environ[env_index]);
	if (max_size >= env_size())
		max_size = realloc_env();
	environ[env_index] = malloc(sizeof(char) * (ft_strlen(name)
		+ ft_strlen(value) + 2));
	ft_strcpy(environ[env_index], name);
	ft_strcat(environ[env_index], "=");
	ft_strcat(environ[env_index], value);
	return (environ[env_index]);
}

void
	ft_unsetenv(char *name)
{
	int				env_index;
	extern char		**environ;

	env_index = ft_igetenv(name);
	if (env_index == -1)
		return ;
	free(environ[env_index]);
	ft_memmove(environ + env_index, environ + env_index + 1,
			sizeof(char *) * (env_size() - env_index));
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
