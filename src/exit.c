/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:54:02 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/23 15:25:29 by smaccary         ###   ########.fr       */
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
		p_builtin_error("exit", av[1], "numeric argument required");
		exit(2);
	}
	if (tab_size(av) > 2)
	{
		p_builtin_error("exit", NULL, "too many arguments");
		return (1);
	}
	exit(0);
	return (1);
}
 