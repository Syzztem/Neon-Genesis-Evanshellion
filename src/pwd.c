/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:55:42 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/01 15:10:04 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

void	builtin_pwd(char **av, char **envp)
{
	char	dir[PATH_MAX];

	(void)av;
	(void)envp;
	getcwd(dir, PATH_MAX);
	ft_putstr_fd(dir, 1);
}
