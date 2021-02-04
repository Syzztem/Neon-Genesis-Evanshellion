/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:24:58 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/04 13:29:19 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **av, char **envp)
{
	size_t	i;
	char	flag;

	(void)envp;
	i = 1;
	flag = 0;
	if (av[1] && !ft_strcmp(av[1], "-n"))
	{
		i = 2;
		flag = 1;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			write(1, " ", 1);
		else if (!flag)
			write(1, "\n", 1);
		++i;
	}
	return (0);
}
