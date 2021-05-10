/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:54:02 by lothieve          #+#    #+#             */
/*   Updated: 2021/05/11 01:42:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	print_exit(void)
{
	if (is_shell_interactive())
	{
		ft_putendl_fd("exit", 1);
		return (1);
	}
	return (0);
}

int
	is_str_num(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	builtin_exit(char **av, char **envp)
{
	(void)av;
	(void)envp;
	print_exit();
	if (av[1] && !is_str_num(av[1]))
	{
		free_env();
		p_builtin_error("exit", av[1], "numeric argument required");
		exit(2);
	}
	if (tab_size(av) > 2)
	{
		p_builtin_error("exit", NULL, "too many arguments");
		return (1);
	}
	free_env();
	if (tab_size(av) == 1)
		exit(g_exit_status);
	exit(ft_atoi(av[1]));
	return (1);
}
