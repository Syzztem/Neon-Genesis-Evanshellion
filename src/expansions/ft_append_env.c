/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 01:37:48 by root              #+#    #+#             */
/*   Updated: 2021/05/03 01:37:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_append_env(char *name, char *value)
{
	int		split_index;
	char	*var;
	char	*new;

	split_index = value - name;
	name[split_index - 2] = 0;
	var = ft_getenv(name);
	new = ft_strjoin(var, value);
	if (!new)
	{
		ft_setenv(name, value);
		return ;
	}
	ft_setenv(name, new);
	free(new);
}
