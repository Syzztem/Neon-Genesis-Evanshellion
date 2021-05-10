/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:22:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/05/09 00:16:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t
	tab_size(char **table)
{
	size_t	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

char
	**dup_tab(char **table)
{
	char	**dup;
	int		size;
	int		i;

	size = tab_size(table);
	dup = ft_calloc(sizeof(char *), size + 1);
	i = -1;
	while (++i < size)
		dup[i] = ft_strdup(table[i]);
	return (dup);
}

void
	free_tab(char **table)
{
	size_t	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

size_t
	argv_len(char **argv)
{
	char	**current;

	current = argv;
	while (*current)
		current++;
	return (current - argv);
}
