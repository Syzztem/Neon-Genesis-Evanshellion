/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:02:05 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/04 13:29:44 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **av, char **envp)
{
	(void)av;
	while (*envp)
	{
		ft_putendl_fd(*envp, 1);
		envp++;
	}
	return (0);
}
