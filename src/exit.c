/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:54:02 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/04 13:30:01 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **av, char **envp)
{
	(void)av;
	(void)envp;
	ft_putendl_fd("exit", 1);
	exit(0);
	return (1);
}
