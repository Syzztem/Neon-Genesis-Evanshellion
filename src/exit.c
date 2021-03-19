/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:54:02 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/19 14:43:55 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **av, char **envp)
{
	(void)av;
	(void)envp;

	if (ft_isatty(0) && ft_isatty(1))
		ft_putendl_fd("exit", 1);
	exit(0);
	return (1);
}
