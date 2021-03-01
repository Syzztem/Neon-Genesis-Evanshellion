/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:42:39 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/01 14:24:37 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define BUILTIN_COUNT 7

static const t_builtin g_builtins[BUILTIN_COUNT + 1] = {
	builtin_echo,
	builtin_exit,
	builtin_cd,
	builtin_env,
	builtin_pwd,
	builtin_unset,
	builtin_export,
	NULL
};

static const char *g_builtin_list[BUILTIN_COUNT + 1] = {
	"echo",
	"exit",
	"cd",
	"env",
	"pwd",
	"unset",
	"export",
	NULL
};

int
	is_builtin(char *command)
{
	int i;

	i = -1;
	while (g_builtin_list[++i])
		if (!ft_strcmp(g_builtin_list[i], command))
			return (i);
	return (-1);
}

void
	exec_builtin(char **av, char **envp)
{
	int i;

	i = is_builtin(*av);
	if (i == -1)
		return ;
	exit(g_builtins[i](av, envp));
}
