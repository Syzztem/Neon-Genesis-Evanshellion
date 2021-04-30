/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:22:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/02 14:31:57 by lothieve         ###   ########.fr       */
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
