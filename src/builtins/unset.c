/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:35:03 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/04 15:09:56 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	is_valid(char *env)
{
	while (*env)
	{
		if (!ft_isalnum(*env) && *env != '_')
			return (0);
		env++;
	}
	return (1);
}

int	builtin_unset(char **av, char **envp)
{
	(void)envp;
	if (!av[1])
		return (0);
	if (!is_valid(av[1]))
	{
		handle_error("minishell: unset: ", av[1], "not a valid identifier");
		return (1);
	}
	ft_unsetenv(av[1]);
	return (0);
}
