/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:54:02 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/21 16:15:21 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	print_exit(void)
{
	if (ft_isatty(0) && ft_isatty(1))
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
	if (tab_size(av) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (!is_str_num(av[1]))
	{
		dprintf(2, "minishell: exit: %s: numeric argument required\n", av[1]);
		exit(2);
	}
	exit(0);
	return (1);
}
 